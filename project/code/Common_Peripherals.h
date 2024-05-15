#ifndef __COMMON_PERIPHERALS_H__
#define __COMMON_PERIPHERALS_H__


//�궨��

#define BUZZER_PIN  (P23_0)

#define LED1                    (P23_7)
#define LED2                    (P23_4)
#define LED3                    (P23_3)
#define LED4                    (P23_1)
#define KEY1                    (P20_0)
#define KEY2                    (P20_1)
#define KEY3                    (P20_2)
#define KEY4                    (P20_3)
#define SWITCH2                 (P21_5)
#define SWITCH1                 (P21_6)


#define SERVO_MOTOR_PWM             (TCPWM_CH61_P17_0)                           // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (50)                                       // ���������϶��Ƶ��  �����ע�ⷶΧ
#define SERVO_MOTOR_MID             (80)                                        //��ֵ75//����ͨ���޸���ֵ�ķ�ʽ�ֲ���е���79
#define SERVO_MOTOR_LMAX            (65)                                        //�����60
#define SERVO_MOTOR_RMAX            (95)                                       //�Ҵ���100

#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))// ------------------ ���ռ�ձȼ��㷽ʽ ------------------


//ȫ�ֱ�������
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;
extern uint8 key_val;
extern float Steer_Value;
//extern int16 x6f_out[6];
extern int   Ctrl_GO_FLAG;
extern int16 encoder; 
extern int16 stand;

void Buzzer_init();//��������ʼ��
void Buzzer_check(int time1,int time2);//������LED��ʼ��
void Key_init();//������LED��ʼ��
void key_scan(void);//����ɨ��
void Steer_init();
void Steer_set(int angle);


void ALL_Init(void);//�ܳ�ʼ��

#endif