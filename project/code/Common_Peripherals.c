#include "zf_common_headfile.h"


//===================================================������===================================================
void Buzzer_init()//��������ʼ��
{
    gpio_init(BUZZER_PIN, GPO, 0, GPO_PUSH_PULL);
}




//===================================================������LED===================================================
// **************************** �������� ****************************
uint8 key1_state = 1;                                                               // ��������״̬
uint8 key2_state = 1;                                                               // ��������״̬
uint8 key3_state = 1;                                                               // ��������״̬
uint8 key4_state = 1;                                                               // ��������״̬

uint8 switch1_state = 0;                                                            // ���뿪�ض���״̬
uint8 switch2_state = 0;                                                            // ���뿪�ض���״̬

uint8 key1_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key2_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key3_state_last = 0;                                                          // ��һ�ΰ�������״̬
uint8 key4_state_last = 0;                                                          // ��һ�ΰ�������״̬

uint8 switch1_state_last = 0;                                                       // ��һ�β��뿪�ض���״̬
uint8 switch2_state_last = 0;                                                       // ��һ�β��뿪�ض���״̬

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

void Key_init()//������LED��ʼ��
{
       gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
       gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED2 ��� Ĭ�ϸߵ�ƽ �������ģʽ
       gpio_init(LED3, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED3 ��� Ĭ�ϸߵ�ƽ �������ģʽ
       gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED4 ��� Ĭ�ϸߵ�ƽ �������ģʽ

       gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������

       gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // ��ʼ�� SWITCH1 ���� Ĭ�ϸߵ�ƽ ��������
       gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_FLOATING_IN);    // ��ʼ�� SWITCH2 ���� Ĭ�ϸߵ�ƽ ��������

}
int count = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
void key_scan()//����ɨ��
{
    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
    

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


//===================================================���===================================================


//float Steer_Value=SERVO_MOTOR_MID;

void Steer_init()//�����ʼ��
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, (uint32)SERVO_MOTOR_DUTY(80));
    //PidInit(&PID_Init);
}

void Steer_set(float angle)//�������
{
//    if(angle<SERVO_MOTOR_LMAX){angle=SERVO_MOTOR_LMAX;}
//    if(angle>SERVO_MOTOR_RMAX){angle=SERVO_MOTOR_RMAX;}
    pwm_set_duty(SERVO_MOTOR_PWM, (uint32)SERVO_MOTOR_DUTY(angle));
}

/*TODO:��Ӷ��ת��ģ����룬��������gps�������ǵĽǶȼ���*/
