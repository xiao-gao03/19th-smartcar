#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "zf_common_typedef.h"

//�궨��
#define MAX_DUTY            (30 )                                              // ���ռ�ձ��������
#define DIR_CH1             (P18_4)                                            // �����������˿�
#define PWM_CH1             (TCPWM_CH51_P18_6)

#define ENCODER1_TIM        (TC_CH58_ENCODER)                                  // ��������ʱ��
#define ENCODER1_PLUS       (TC_CH58_ENCODER_CH1_P17_3)                        // �����������˿�
#define ENCODER1_DIR        (TC_CH58_ENCODER_CH2_P17_4)                        // �����������ֵ�˿�

void motor_init();
void motor_run(int16 dir,int32 speed);
void motor_stop();
void motor_off();
void HALL_gather();
void BLDC_Cloop_ctrl(int16 dir,int32 SPEED);
#endif

