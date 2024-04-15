#include "zf_common_headfile.h"



//--------------------------------------------------------------
//����ģ��
//--------------------------------------------------------------

/*!
  * @file     LQ_VoiceProcess.c
  *
  * @brief    �ű���������
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020��4��27��
  */ 



#include <Main.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>




/**
 * adc�ɼ����ݳ���
 */
#define ADC_DATA_LEN    2048

/*
 * adc�ɼ���ɱ�־λ
 */
volatile uint8  AdcFinishFlag = 0;

/*
 * adc˫buff������  ������ɵ��������
 */
volatile uint8  AdcBuffIndex = 0;

/*
 * adc�����±�
 */
volatile uint32 adcCount = 0;

/*
 * ADC����   adc0 1 2 3 �ɼ���˷��ź�
 *
 *     2     1
 *
 *     3     0
 */
__attribute__ ((aligned(256)))  volatile int16_t g_adc0Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc1Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc2Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc3Data[2][ADC_DATA_LEN];


/*
 * ����ؽ��
 */
float g_acor1[2][30];
float g_acor2[2][30];
float g_acor3[2][30];
float g_acor4[2][30];

/*
 * С���Ƕ�
 */
float g_Angle   = 0;






/*!
  * @brief    �ű�һЩ��ʼ������
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ��
  *
  * @date     2020/4/28
  */
void VoiceInit(void)
{
	adc_init(ADC0, 1000000); //��ʼ��
	adc_init(ADC1, 1000000); //��ʼ��
	adc_init(ADC2, 1000000); //��ʼ��
	adc_init(ADC3, 1000000); //��ʼ��
//TODO:�޸�ΪPIT�ж�
	CCU6_InitConfig(CCU60, CCU6_Channel0, 100);  //100us����һ���ж�  �ж��вɼ�adc����

}

/*!
  * @brief    ccu6 �ɼ��жϷ�����   �����źŲɼ�
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ��
  *
  * @date     2020/4/28
  */
void VoiceGetSample(void)
{
	static uint8 adcIndex = 0;

	if(adcCount >= ADC_DATA_LEN)
	{
		adcCount = 0;
		AdcFinishFlag = 1;

		/* �л�buff������ */
		if(adcIndex == 0)
		{
			adcIndex = 1;
			AdcBuffIndex = 0;
		}
		else
		{
			adcIndex = 0;
			AdcBuffIndex = 1;
		}
	}

	if(AdcFinishFlag == 0)
	{
//		g_adc1Data[adcIndex][adcCount] = ADC_ReadAverage(ADC1, 3);
//		g_adc2Data[adcIndex][adcCount] = ADC_ReadAverage(ADC2, 3);
//		g_adc3Data[adcIndex][adcCount] = ADC_ReadAverage(ADC3, 3);
//		g_adc0Data[adcIndex][adcCount] = ADC_ReadAverage(ADC0, 3);

		g_adc0Data[adcIndex][adcCount] = adc_convert(ADC0);
		g_adc1Data[adcIndex][adcCount] = adc_convert(ADC1);
		g_adc2Data[adcIndex][adcCount] = adc_convert(ADC2);
		g_adc3Data[adcIndex][adcCount] = adc_convert(ADC3);

		adcCount++;
	}

}



/*!
  * @brief    ��һ������
  *
  * @param    x   �� Ҫ��������
  * @param    len �� Ҫ�������ݳ���
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see
  *
  * @date     2020/4/28
  */
void Normal(int16_t *x, uint16 len)
{
	float sum = 0;
	int   i;

	for(i = 0; i < len; i++)
	{
		sum += x[i];
	}

	sum = sum / len;


	for(i = 0; i < len; i++)
	{
		x[i] -= sum;
	}
}

/*!
  * @brief    �����
  *
  * @param    acor1��  y0 y1 ����ؽ��
  * @param    acor2��  y1 y2����ؽ��
  * @param    acor3��  y0 y2����ؽ��
  * @param    acor4��  y1 y3����ؽ��
  * @param    y0   �� ��������� y0
  * @param    y1   �� ��������� y1
  * @param    y2   �� ��������� y2
  * @param    y3   �� ��������� y3
  * @param    len  �� ��������ݳ���
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see
  *
  * @date     2020/4/28
  */
void Xcorr(float *acor1, float *acor2, float *acor3, float *acor4, int16_t *y0, int16_t *y1, int16_t *y2, int16_t *y3, uint16 len)
{
	float sum3 = 0;
	float sum4 = 0;
	float sum1 = 0;
	float sum2 = 0;
	int delay, i, j;
	for(delay = -15; delay < 15; delay++)
//	for(delay = -len + 1; delay < len; delay++)
	{
		sum1 = 0;
		sum2 = 0;
		sum3 = 0;
		sum4 = 0;
		for(i = 0; i < len; i++)
		{
			j = i + delay;
			if((j < 0))
			{
				sum1 += 0.0001f * y0[j + len] * y1[i];
				sum2 += 0.0001f * y1[j + len] * y2[i];
				sum3 += 0.0001f * y0[j + len] * y2[i];
				sum4 += 0.0001f * y1[j + len] * y3[i];
			}
			else if ((j >= len))
			{
				sum1 += 0.0001f * y0[j - len] * y1[i];
				sum2 += 0.0001f * y1[j - len] * y2[i];
				sum3 += 0.0001f * y0[j - len] * y2[i];
				sum4 += 0.0001f * y1[j - len] * y3[i];
			}
			else
			{
				sum1 += 0.0001f * y0[j] * y1[i];
				sum2 += 0.0001f * y1[j] * y2[i];
				sum3 += 0.0001f * y0[j] * y2[i];
				sum4 += 0.0001f * y1[j] * y3[i];
			}
		}
		acor1[15 + delay] = (float)sum1;
		acor2[15 + delay] = (float)sum2;
		acor3[15 + delay] = (float)sum3;
		acor4[15 + delay] = (float)sum4;
	}
}



/*!
  * @brief    �õ�������λ��
  *
  * @param    acor1�� ����ؽ��
  * @param    acor2�� ����ؽ��
  * @param    acor3�� ����ؽ��
  * @param    acor4�� ����ؽ��
  * @param    len  �� ���ݳ���
  * @param    index�� �����ؽ�����ֵ�±�
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see
  *
  * @date     2020/4/28
  */
void SeekMaxAcor(float * acor1, float * acor2, float *acor3, float *acor4, int16_t len, int16_t *index)
{
	int16_t i = 0;

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	index[3] = 0;
	for(i = 1; i < len; i++)
	{
		if(acor1[i] > acor1[index[0]])
		{
			index[0] = i;
		}
		if(acor2[i] > acor2[index[1]])
		{
			index[1] = i;
		}
		if(acor3[i] > acor3[index[2]])
		{
			index[2] = i;
		}
		if(acor4[i] > acor4[index[3]])
		{
			index[3] = i;
		}
	}

	index[0] = len/2 - index[0];
	index[1] = len/2 - index[1];
	index[2] = len/2 - index[2];
	index[3] = len/2 - index[3];
}


/*!
  * @brief    ��˷����ݴ���  ��ȡ�Ƕ���Ϣ
  *
  * @param    ��
  *
  * @return   ������λ��
  *
  * @note     ��
  *
  * @see
  *
  * @date     2020/4/28
  */
void VoiceProcess(void)
{

	if(AdcFinishFlag)
	{
		/* ���ݴ���    */
		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);

		for(int i = 0; i < ADC_DATA_LEN; i ++)
		{
          /* �ϱ�������λ��  ��ԭʼ���ݲ��� */
			ANO_DT_send_int16(g_adc0Data[AdcBuffIndex][i], g_adc1Data[AdcBuffIndex][i], g_adc2Data[AdcBuffIndex][i], g_adc3Data[AdcBuffIndex][i], 0, 0, 0, 0);
		}

		AdcFinishFlag = 0;
	}


//	if(AdcFinishFlag)
//	{
//		char txt[32];
//
//		/* �����ط�ֵ�±� */
//		int16_t acorIndex[4];
//
//		/* ��¼ʱ�� */
//		uint32_t nowTime = STM_GetNowUs(STM0);
//
//		/* ���ݴ���    */
//		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
//		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
//		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
//		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);
//
//		/* ����� */
//        Xcorr((float *)&g_acor1[AdcBuffIndex], (float *)&g_acor2[AdcBuffIndex], (float *)&g_acor3[AdcBuffIndex], (float *)&g_acor4[AdcBuffIndex], (int16_t *)&g_adc0Data[AdcBuffIndex], (int16_t *)&g_adc1Data[AdcBuffIndex], (int16_t *)&g_adc2Data[AdcBuffIndex], (int16_t *)&g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);
//
//		/** ��ȡ�����ط�ֵ  */
//		SeekMaxAcor((float *)&g_acor1[AdcBuffIndex], (float *)&g_acor2[AdcBuffIndex], (float *)&g_acor3[AdcBuffIndex], (float *)&g_acor4[AdcBuffIndex], 30, acorIndex);
//
//		/* ����������� �����С����±� */
//		uint8_t IndexMax = 0, IndexMin = 0;
//
//		/** �ҵ�����ֵ��С������ֵ�±� */
//		for(uint8_t i = 1; i < 4; i++)
//		{
//			if(abs(acorIndex[i]) >= abs(acorIndex[IndexMax]))
//			{
//				IndexMax = i;
//			}
//			if(abs(acorIndex[i]) <= abs(acorIndex[IndexMin]))
//			{
//				IndexMin = i;
//			}
//		}
//
//		/* �жϴ��·�λ */
//		if(IndexMin == 0)
//		{
//			if(acorIndex[1] > 0)
//			{
//				g_Angle = 0;
//			}
//			else
//			{
//				g_Angle = 180;
//			}
//		}
//
//		else if(IndexMin == 1)
//		{
//			if(acorIndex[0] > 0)
//			{
//				g_Angle = 270;
//			}
//			else
//			{
//				g_Angle = 90;
//			}
//		}
//
//		else if(IndexMin == 2)
//		{
//			if(acorIndex[3] > 0)
//			{
//				g_Angle = 45;
//			}
//			else
//			{
//				g_Angle = 225;
//			}
//		}
//
//		else if(IndexMin == 3)
//		{
//			if(acorIndex[2] > 0)
//			{
//				g_Angle = 315;
//			}
//			else
//			{
//				g_Angle = 135;
//			}
//		}
//
//
//		nowTime = STM_GetNowUs(STM0) - nowTime;
//
//		if(IfxCpu_acquireMutex(&mutexTFTIsOk))
//		{
//			/* ��ʾ���� */
//			sprintf(txt, "%-3d %-3d %-3d %-3d", acorIndex[0], acorIndex[1], acorIndex[2], acorIndex[3]);
//			TFTSPI_P8X16Str(0, 2, txt, u16WHITE, u16BLUE);		//�ַ�����ʾ
//
//
//			sprintf(txt, "index: % 5d", nowTime);               //��ʾ����ʱ��
//			TFTSPI_P8X16Str(0, 6, txt, u16WHITE, u16BLUE);		//�ַ�����ʾ
//
//			sprintf(txt, "angle: %-5.2f", g_Angle);             //��ʾ�Ƕ���Ϣ
//			TFTSPI_P8X16Str(0, 4, txt, u16WHITE, u16BLUE);		//�ַ�����ʾ
//
//			IfxCpu_releaseMutex(&mutexTFTIsOk);
//		}
//
//
//		AdcFinishFlag = 0;
//	}
}

