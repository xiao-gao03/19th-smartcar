#include "zf_common_headfile.h"

int16 Target_speed=0;
int16 Current_speed=0;
int16 Gap=0;
int32 OUT=0;
int16 encoder=0;  //转速
int16 stand=0;
int16 Dir ;

//电机初始化，打开PWM_CH1通道，频率设置1kHz
void motor_init()
{
    pwm_init(PWM_CH1, 1000, 0);                                                 // PWM 通道1 初始化频率1KHz 占空比初始为0
    gpio_init(DIR_CH1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                          // 初始化电机方向输出引脚
    encoder_dir_init(ENCODER1_TIM, ENCODER1_PLUS, ENCODER1_DIR);                // 初始化编码器采值引脚及定时器
}


//电机运行，设置PWM占空比duty
/**
 *
 * @param dir  电机方向
 * @param speed 电机速度  max==10000；
 */
void motor_run(int16 dir,int32 speed)
{
    //int duty = speed * (PWM_DUTY_MAX / 100);
    if(dir == 1)                                            //正转
    {
        pwm_set_duty(PWM_CH1, speed);
        gpio_set_level(DIR_CH1,1);
    }
    else if(dir == 0)                                                   //反转
    {
        pwm_set_duty(PWM_CH1, -speed);
        gpio_set_level(DIR_CH1, 0);
    }
    else
    {
        printf("Motor direction error!\n");
    }
}

/**
 * @brief BLDC闭环控制
 * 
 * @param dir   电机方向
 * @param SPEED 电机速度  max==10000；
 */
void BLDC_Cloop_ctrl(int16 dir,int32 SPEED) //BLDC闭环控制
{
    Dir = dir;
    Target_speed=SPEED;      //目标速度
    Current_speed= encoder;   //当前速度
    Gap=Target_speed-Current_speed;       //速度差距


    OUT=PidIncCtrl(&PID_MOTOR,(float)Gap);
    if(OUT> 10000) {OUT=10000;}
    if(OUT<-10000) {OUT=-10000;}

    motor_run(Dir,OUT);
}


//刹车函数
void motor_stop()
{
    if(Dir == 1)
    {
        BLDC_Cloop_ctrl(1,0);
    }
    else
    {
        BLDC_Cloop_ctrl(0,0);
    }

}


//停止输出PWM靠摩擦力刹车or紧急停车
void motor_off()
{
    pwm_all_channel_close();
}

//===================================================霍尔编码器===================================================


void HALL_init()//霍尔编码器初始化
{
    encoder_dir_init(ENCODER1_TIM,ENCODER1_PLUS,ENCODER1_DIR);
}

uint16 HALL_gather()//霍尔编码器获取值
{

    encoder= (encoder_get_count(ENCODER1_TIM));
    encoder_clear_count(ENCODER1_TIM);                                // 采集对应编码器数据
    return encoder;
}

