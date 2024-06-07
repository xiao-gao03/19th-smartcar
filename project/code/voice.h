#ifndef __VOICE_H__
#define __VOICE_H__

/*!
  * @file     LQ_SmartCar.h
  *
  * @brief    
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
#ifndef SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_
#define SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_



#define ADC0          (ADC0_CH00_P06_0)
#define ADC1          (ADC0_CH01_P06_1)
#define ADC2          (ADC0_CH02_P06_2)
#define ADC3          (ADC0_CH03_P06_3)

/*
 * С���Ƕ�
 */
extern float g_Angle;
extern int lf,lb,rf,rb;
extern float a,b,c,d;
void VoiceInit(void);

void VoiceProcess(void);

void VoiceGetSample(void);

#endif /* SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_ */


#endif