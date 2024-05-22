#include "zf_common_headfile.h"

int16 Target_speed=0;
int16 Current_speed=0;
int16 Gap=0;
int32 OUT=0;
int16 encoder=0;  //ת��
int16 stand=0;
int16 Dir ;

//�����ʼ������PWM_CH1ͨ����Ƶ������1kHz
void motor_init()
{
    pwm_init(PWM_CH1, 1000, 0);                                                 // PWM ͨ��1 ��ʼ��Ƶ��1KHz ռ�ձȳ�ʼΪ0
    gpio_init(DIR_CH1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                          // ��ʼ����������������
    encoder_dir_init(ENCODER1_TIM, ENCODER1_PLUS, ENCODER1_DIR);                // ��ʼ����������ֵ���ż���ʱ��
}


//������У�����PWMռ�ձ�duty
/**
 *
 * @param dir  �������
 * @param speed ����ٶ�  max==10000��
 */
void motor_run(int16 dir,int32 speed)
{
    //int duty = speed * (PWM_DUTY_MAX / 100);
    if(dir == 1)                                            //��ת
    {
        pwm_set_duty(PWM_CH1, speed);
        gpio_set_level(DIR_CH1,1);
    }
    else if(dir == 0)                                                   //��ת
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
 * @brief BLDC�ջ�����
 * 
 * @param dir   �������
 * @param SPEED ����ٶ�  max==10000��
 */
void BLDC_Cloop_ctrl(int16 dir,int32 SPEED) //BLDC�ջ�����
{
    Dir = dir;
    Target_speed=SPEED;      //Ŀ���ٶ�
    Current_speed= encoder;   //��ǰ�ٶ�
    Gap=Target_speed-Current_speed;       //�ٶȲ��


    OUT=PidIncCtrl(&PID_MOTOR,(float)Gap);
    if(OUT> 10000) {OUT=10000;}
    if(OUT<-10000) {OUT=-10000;}

    motor_run(Dir,OUT);
}


//ɲ������
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


//ֹͣ���PWM��Ħ����ɲ��or����ͣ��
void motor_off()
{
    pwm_all_channel_close();
}

//===================================================����������===================================================


void HALL_init()//������������ʼ��
{
    encoder_dir_init(ENCODER1_TIM,ENCODER1_PLUS,ENCODER1_DIR);
}

uint16 HALL_gather()//������������ȡֵ
{

    encoder= (encoder_get_count(ENCODER1_TIM));
    encoder_clear_count(ENCODER1_TIM);                                // �ɼ���Ӧ����������
    return encoder;
}

