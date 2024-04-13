#include "zf_common_headfile.h"

int16 Target_speed=0;
int16 Current_speed=0;
int16 Gap=0;
int32 OUT=0;
int16 encoder=0;  //ת��
int16 stand=0;


//�����ʼ������PWM_CH1ͨ����Ƶ������1kHz
void motor_init()
{
    pwm_init(PWM_CH1, 1000, 0);                                                 // PWM ͨ��1 ��ʼ��Ƶ��1KHz ռ�ձȳ�ʼΪ0
    gpio_init(DIR_CH1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                          // ��ʼ����������������
    encoder_dir_init(ENCODER1_TIM, ENCODER1_PLUS, ENCODER1_DIR);                // ��ʼ����������ֵ���ż���ʱ��
}


//������У�����PWMռ�ձ�duty
void motor_run(int16 speed)
{
    int duty = speed * (PWM_DUTY_MAX / 100);
    if(duty>=0)//��ת
    {
        pwm_set_duty(PWM_CH1, duty);
        gpio_set_level(DIR_CH1,1);
    }
    else             //��ת
    {
        pwm_set_duty(PWM_CH1, -duty);
        gpio_set_level(DIR_CH1,0);
    }
}


void BLDC_Cloop_ctrl(int16 SPEED) //BLDC�ջ�����
{

    Target_speed=SPEED;      //Ŀ���ٶ�
    Current_speed= encoder;   //��ǰ�ٶ�
    Gap=Target_speed-Current_speed;       //�ٶȲ��


    OUT=PidIncCtrl(&PID_MOTOR,(float)Gap);
    if(OUT> 10000) {OUT=10000;}
    if(OUT<-10000) {OUT=-10000;}

    motor_run((int16)OUT);
}


//ɲ������
void motor_stop()
{

}


//ֹͣ���PWM��Ħ����ɲ��
void motor_off()
{
    pwm_all_channel_close();
}

//===================================================����������===================================================


void HALL_init()//������������ʼ��
{
    encoder_dir_init(ENCODER1_TIM,ENCODER1_PLUS,ENCODER1_DIR);
}

void HALL_gather()//������������ȡֵ
{

    encoder= (encoder_get_count(ENCODER1_TIM));
    encoder_clear_count(ENCODER1_TIM);                                // �ɼ���Ӧ����������
}

