#include "zf_common_headfile.h"

double angle;
double SERVO_angle;
//***************************************************************************************
                       /*�˶��߼���������*/
//***************************************************************************************


/*TODO:���ѭ��ģ�����
        1.��ȡС��Ŀǰ�ĽǶ�
        2.��ȡgps��õ�Ŀ��ľ�γ��
        3.����Ŀ�꾭γ������������ļн�
        4.����Ŀǰ�Ƕ���Ŀ��ǶȵĲ�ֵ��?��
        5.����������ת��ĽǶ�
        
        PS�����������+-60��͵���
            ͬ����ȡ���Ϸ�����������ת��Ƕȣ�������ת��*/
/**
 * ����λ��ת����������gps��360��ת����0-180
 * @param angle �õ��ĽǶ�
 */
void car_ang_trans(double angle)
{
    if(gnss.direction >= 0 && gnss.direction <=180)
    {
        angle = gnss.direction;
    }
    else if(gnss.direction > 180 &&gnss.direction <= 360)
    {
        angle = gnss.direction - 180;
    }
}

void ang_trans(float angle)
{
    if(angle > 180 && angle <= 360)
    {
        angle = angle - 180;
    }
}

/**
 * gps��imu�����˲��õ�yaw
 * @param a
 * @param b
 * @param alpha
 * @return
 */
void ComplementaryFilter(float a, float b, float alpha,float angle) {
    // alpha ���˲�ϵ������Χ��0��1֮��
    // alpha Խ�ӽ� 1��a ��Ӱ��Խ��
    // alpha Խ�ӽ� 0��b ��Ӱ��Խ��
    angle = alpha * a + (1 - alpha) * b;
}

void turn_angle(double angle)
{
    if(angle >= 15)
    {
        SERVO_MOTOR_DUTY(SERVO_MOTOR_RMAX);
    }
    else if(angle <= -15)
    {
        SERVO_MOTOR_DUTY(SERVO_MOTOR_LMAX);
    }
    else if(angle > -15 && angle <15)
    {
        SERVO_MOTOR_DUTY(SERVO_MOTOR_MID + angle);
    }
}