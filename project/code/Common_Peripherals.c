#include "zf_common_headfile.h"


//===================================================蜂鸣器===================================================
void Buzzer_init()//蜂鸣器初始化
{
    gpio_init(BUZZER_PIN, GPO, 0, GPO_PUSH_PULL);
}




//===================================================按键与LED===================================================
// **************************** 变量定义 ****************************
uint8 key1_state = 1;                                                               // 按键动作状态
uint8 key2_state = 1;                                                               // 按键动作状态
uint8 key3_state = 1;                                                               // 按键动作状态
uint8 key4_state = 1;                                                               // 按键动作状态

uint8 switch1_state = 0;                                                            // 拨码开关动作状态
uint8 switch2_state = 0;                                                            // 拨码开关动作状态

uint8 key1_state_last = 0;                                                          // 上一次按键动作状态
uint8 key2_state_last = 0;                                                          // 上一次按键动作状态
uint8 key3_state_last = 0;                                                          // 上一次按键动作状态
uint8 key4_state_last = 0;                                                          // 上一次按键动作状态

uint8 switch1_state_last = 0;                                                       // 上一次拨码开关动作状态
uint8 switch2_state_last = 0;                                                       // 上一次拨码开关动作状态

uint8 key1_flag = 0;
uint8 key2_flag = 0;
uint8 key3_flag = 0;
uint8 key4_flag = 0;

uint8 key_val;

uint8 switch1_flag;
uint8 switch2_flag;

uint16 key1_count=-1;
uint16 key2_count=-1;
uint16 key3_count=-1;
uint16 key4_count=-1;

uint16 switch1_count=-1;
uint16 switch2_count=-1;

uint16_t key1_f = 1;
uint16_t key2_f = 1;
uint16_t key3_f = 1;
uint16_t key4_f = 1;

void Key_init()//按键与LED初始化
{
       gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED1 输出 默认高电平 推挽输出模式
       gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED2 输出 默认高电平 推挽输出模式
       gpio_init(LED3, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED3 输出 默认高电平 推挽输出模式
       gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // 初始化 LED4 输出 默认高电平 推挽输出模式

       gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
       gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
       gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
       gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入

       gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // 初始化 SWITCH1 输入 默认高电平 浮空输入
       gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // 初始化 SWITCH2 输入 默认高电平 浮空输入

}
int count = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
void key_scan()//按键扫描
{
    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
    

    key1_state = gpio_get_level(KEY1);
    key2_state = gpio_get_level(KEY2);
    key3_state = gpio_get_level(KEY3);
    key4_state = gpio_get_level(KEY4);
    switch1_flag = gpio_get_level(SWITCH1);
    switch2_flag = gpio_get_level(SWITCH2);

    if(key1_state != 1 && key1_f == 1)
    {
        count++;
        if(count >10)
        {
            count = 0;
            key1_flag = 1;
            gpio_set_level(LED1,0);
            key1_f = 0;
        }
    }
    if(key1_state == 1)
    {
        count = 0;
        key1_f = 1;
        key1_flag = 0;
        gpio_set_level(LED1,1);
    }
    
    if(key2_state != 1 && key2_f == 1)
    {
        count2++;
        if(count2 >10)
        {
            count2 = 0;
            key2_flag = 1;
            gpio_set_level(LED2,0);
            key2_f = 0;
        }
    }
    if(key2_state == 1)
    {
        count2 = 0;
        key2_f = 1;
        key2_flag = 0;
        gpio_set_level(LED2,1);
    }

    if(key3_state != 1 && key3_f == 1)
    {
        count3++;
        if(count3 >10)
        {
            count3 = 0;
            key3_flag = 1;
            gpio_set_level(LED3,0);
            key3_f = 0;
        }
    }
    if(key3_state == 1)
    {
        count3 = 0;
        key3_f = 1;
        key3_flag = 0;
        gpio_set_level(LED3,1);
    }

    if(key4_state != 1 && key4_f == 1)
    {
        count4++;
        if(count4 >10)
        {
            count4 = 0;
            key4_flag = 1;
            gpio_set_level(LED4,0);
            key4_f = 0;
        }
    }
    if(key4_state == 1)
    {
        count4 = 0;
        key4_f = 1;
        key4_flag = 0;
        gpio_set_level(LED4,1);
    }


}


//===================================================舵机===================================================


//float Steer_Value=SERVO_MOTOR_MID;

void Steer_init()//舵机初始化
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, (uint32)SERVO_MOTOR_DUTY(80));
    //PidInit(&PID_Init);
}

void Steer_set(float angle)//舵机驱动
{
//    if(angle<SERVO_MOTOR_LMAX){angle=SERVO_MOTOR_LMAX;}
//    if(angle>SERVO_MOTOR_RMAX){angle=SERVO_MOTOR_RMAX;}
    pwm_set_duty(SERVO_MOTOR_PWM, (uint32)SERVO_MOTOR_DUTY(angle));
}

/*TODO:添加舵机转向模块代码，需搭配硅麦，gps，陀螺仪的角度计算*/
