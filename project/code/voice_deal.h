#include "zf_common_headfile.h"
#ifndef _voice_deal_H_
#define _voice_deal_H_

#define MIC_PIN1  (ADC0_CH00_P06_0)
#define MIC_PIN2  (ADC0_CH02_P06_2)
#define MIC_PIN3  (ADC0_CH03_P06_3)
#define MIC_PIN4  (ADC0_CH01_P06_1)
#define sample_point 2048

extern int32 ADC[4];
extern int16 SUM_delay12;
extern int16 SUM_delay34;
extern float mic_angle;
void mic_data_get(void);
void mic_data_copy(void);
void Mic_init(void);
int16 Micdata_cov(int16* data1, int16* data2, unsigned short point, short point1, short point2, unsigned short step);
void Mic_Process(void);
#endif
