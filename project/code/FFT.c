/*********************************************************************************************************************
* CYT4BB Opensourec Library ���� CYT4BB ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� CYT4BB ��Դ���һ����
*
* CYT4BB ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main_cm7_0
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT4BB
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2024-1-4       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "arm_math.h"

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� CMSIS-DAP ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� P14_0
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� P14_1
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ

// ***************************** ���̲���˵�� *****************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ��������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.��������������Ͽ������´�����Ϣ��
// fft count use time: 876 us
//
// ifft count use time: 964 us
// 5.������������ֵ�ʾ�������濴��FFT������ɺ�Ľ������
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�

// **************************** �������� ****************************

             

float inputSignal_1[FFT_SIZE * 2];                // ���������ź� �����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2
float fft_outputSignal_1[FFT_SIZE * 2];           // ����FFT����ź� ����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2

float inputSignal_2[FFT_SIZE * 2];                // ���������ź� �����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2
float fft_outputSignal_2[FFT_SIZE * 2];           // ����FFT����ź� ����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2

float inputSignal_3[FFT_SIZE * 2];                // ���������ź� �����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2
float fft_outputSignal_3[FFT_SIZE * 2];           // ����FFT����ź� ����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2

float inputSignal_0[FFT_SIZE * 2];                // ���������ź� �����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2
float fft_outputSignal_0[FFT_SIZE * 2];           // ����FFT����ź� ����ź�Ϊ���� ���Գ���Ϊ FFT_SIZE * 2

int adc_flag = 0;
int p = 0;

uint32 fft_count_time_us  = 0;
uint32 ifft_count_time_us = 0;
arm_cfft_instance_f32 arm_cfft_instance_f32_len_2048;                       // ����FFT����

extern int adc_flag;

    // **************************** �ź�Ԥ���� ****************************
//    for(int i = 0; i < FFT_SIZE; i++){
//        // �������������⸳ֵ������ģ������һ��500hz�����Ҳ��ź�
//        // ʵ�������ź���ADC�ɼ�
//        // �������ź�����ʵ�����鲿Ϊ0(FFT����ʹ�ø�����float����ĸ����洢��ʽΪʵ���鲿����洢)
//        inputSignal[2 * i] = /*adc_convert(ADC0_CH00_P06_0);*/ arm_sin_f32(FFT_DEMO_PI * i / 10);
//        inputSignal[2*i + 1] = 0;
//    }    
    // **************************** �ź�Ԥ���� ****************************
    
void FFT_Init()
{          
    arm_cfft_init_f32(&arm_cfft_instance_f32_len_2048, FFT_SIZE);               // ��ʼ��FFT���� ������㳤��   
    // adc_init(ADC0_CH00_P06_0,ADC_12BIT);
    // pit_us_init(PIT_CH0,100);
}
    // **************************** ��ʼ������ ****************************
    
    
    // ************************** ��������� *************************** 
    
    
    // ****************************** �ܽ� ******************************* 
    // ����ͨ��������ֵ�ʾ�����۲쵽FFT�������У��������±�Ϊ 103 ��λ�õ�ֵ��󣬴�ʱ����ģ��������ź�Ƶ��
    // ����Ƶ��Ϊ10khz��FFT���㳤��Ϊ2048�����ݣ���ôFFTƵ�ʵ���Ϊ 10000 ���� 2048 ���� 4.8828125 hz����ζ��FFT�������ļ��Ϊ4.8828125 hz
    // ��������±�Ϊ 103 ��λ�õ�Ƶ������ 103 * 4.8828125 = 502.9296875 hz����ʱ���Դ�ŵó�ԭ�ź�Ƶ��(û��׼ȷ�������500hz����Ϊ�м��㾫�����)
    // ****************************** �ܽ� ******************************* 

void FFT_comp()
{
  if(adc_flag == 1)
    {

      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_0 , 0 , 1);        // 32λ����FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_1 , 0 , 1);        // 32λ����FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_2 , 0 , 1);        // 32λ����FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_3 , 0 , 1);        // 32λ����FFT����(���������滻ԭinputSignal������)

      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_0 , FFT_SIZE);               // ��FFT���ת��Ϊ������(ת����������Ϊ�˹۲첨��)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_1 , FFT_SIZE);               // ��FFT���ת��Ϊ������(ת����������Ϊ�˹۲첨��)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_2 , FFT_SIZE);               // ��FFT���ת��Ϊ������(ת����������Ϊ�˹۲첨��)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_3 , FFT_SIZE);               // ��FFT���ת��Ϊ������(ת����������Ϊ�˹۲첨��)

      for(int i = 0; i < FFT_SIZE; i++)
      {
        if(i*4.8828125 < 1699 || i*4.8828125 > 1704)
        {
          fft_outputSignal_0[i] = 0;
          fft_outputSignal_1[i] = 0;
          fft_outputSignal_2[i] = 0;
          fft_outputSignal_3[i] = 0;
        }
      }

      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_0 , 1 , 1);        // 32λ������FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_1 , 1 , 1);        // 32λ������FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_2 , 1 , 1);        // 32λ������FFT����(���������滻ԭinputSignal������)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_3 , 1 , 1);        // 32λ������FFT����(���������滻ԭinputSignal������)
      
//      for(int i = 0; i < FFT_SIZE; i++)
//      {
//          printf("%f,%f,\t%f,\t\t%f,\t%f,\t%f,\t%f,\t%f,\t%f\n",fft_outputSignal_0[i],inputSignal_0[i * 2],fft_outputSignal_1[i],inputSignal_1[i * 2],fft_outputSignal_2[i],inputSignal_2[i * 2],fft_outputSignal_3[i],inputSignal_3[i * 2],i*4.8828125);
//        
//      }   
      
//        printf("\r\n fft count use time: %d us\r\n",   fft_count_time_us);          // ���FFT�����ʱ
//        printf("\r\n ifft count use time: %d us\r\n", ifft_count_time_us);          // �����FFT�����ʱ
//      adc_flag =0;
    }
}


void FFT_capture()
{
    if(adc_flag == 0)
    {
      if(p < FFT_SIZE)
      {
        inputSignal_0[2 * p] = adc_convert(ADC0_CH00_P06_0);
        inputSignal_0[2*p + 1] = 0;

        inputSignal_1[2 * p] = adc_convert(ADC0_CH01_P06_1);
        inputSignal_1[2*p + 1] = 0;

        inputSignal_2[2 * p] = adc_convert(ADC0_CH02_P06_2);
        inputSignal_2[2*p + 1] = 0;

        inputSignal_3[2 * p] = adc_convert(ADC0_CH03_P06_3);
        inputSignal_3[2*p + 1] = 0;
        p++;
      }
      else if(p >= FFT_SIZE)
      {
        adc_flag = 1;
      }
    }
}
      

