#ifndef __VOICE_H__
#define __VOICE_H__

/*!
  * @file     LQ_SmartCar.h
  *
  * @brief    
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     Tab键 4个空格
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020年4月27日
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_
#define SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_



#define ADC0          (ADC0_CH00_P06_0)
#define ADC1          (ADC0_CH01_P06_1)
#define ADC2          (ADC0_CH02_P06_2)
#define ADC3          (ADC0_CH03_P06_3)

/*
 * 小车角度
 */
extern float g_Angle;
extern int lf,lb,rf,rb;
extern float a,b,c,d;
void VoiceInit(void);

void VoiceProcess(void);

void VoiceGetSample(void);

#endif /* SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_ */


#endif