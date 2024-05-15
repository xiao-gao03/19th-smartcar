#ifndef __COMMON_PERIPHERALS_H__
#define __COMMON_PERIPHERALS_H__


//宏定义

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


#define SERVO_MOTOR_PWM             (TCPWM_CH61_P17_0)                           // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50)                                       // 定义主板上舵机频率  请务必注意范围
#define SERVO_MOTOR_MID             (80)                                        //中值75//可以通过修改中值的方式弥补机械误差79
#define SERVO_MOTOR_LMAX            (65)                                        //左打死60
#define SERVO_MOTOR_RMAX            (95)                                       //右打死100

#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))// ------------------ 舵机占空比计算方式 ------------------


//全局变量声明
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

void Buzzer_init();//蜂鸣器初始化
void Buzzer_check(int time1,int time2);//按键与LED初始化
void Key_init();//按键与LED初始化
void key_scan(void);//按键扫描
void Steer_init();
void Steer_set(int angle);


void ALL_Init(void);//总初始化

#endif