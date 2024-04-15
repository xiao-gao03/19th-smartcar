#ifndef __MOTOR_H__
#define __MOTOR_H__

//�궨��
#define MAX_DUTY            (70 )                                              // ���ռ�ձ��������
#define DIR_CH1             (P18_1)                                            // �����������˿�
#define PWM_CH1             (TCPWM_CH54_P18_3)

#define ENCODER1_TIM        (TC_CH58_ENCODER)                                  // ��������ʱ��
#define ENCODER1_PLUS       (TC_CH58_ENCODER_CH1_P17_3)                        // �����������˿�
#define ENCODER1_DIR        (TC_CH58_ENCODER_CH2_P17_4)                        // �����������ֵ�˿�

void motor_init();
void motor_run(int16 speed);
void motor_stop();
void motor_off();
void HALL_init();
void HALL_gather();
void BLDC_Cloop_ctrl(int16 SPEED);
#endif

