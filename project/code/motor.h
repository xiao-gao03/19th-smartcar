#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "zf_common_typedef.h"

//宏定义
#define MAX_DUTY            (30 )                                              // 最大占空比输出限制
#define DIR_CH1             (P18_4)                                            // 电机方向输出端口
#define PWM_CH1             (TCPWM_CH51_P18_6)

#define ENCODER1_TIM        (TC_CH58_ENCODER)                                  // 编码器定时器
#define ENCODER1_PLUS       (TC_CH58_ENCODER_CH1_P17_3)                        // 编码器计数端口
#define ENCODER1_DIR        (TC_CH58_ENCODER_CH2_P17_4)                        // 编码器方向采值端口

void motor_init();
void motor_run(int16 dir,int32 speed);
void motor_stop();
void motor_off();
void HALL_gather();
void BLDC_Cloop_ctrl(int16 dir,int32 SPEED);
#endif

