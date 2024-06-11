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
double car_ang_trans(double angle0)
{
    double cor_slef_angle;
    if(angle0 > 180 && angle0 <= 360)
    {
        cor_slef_angle = angle0 - 360;
    }
    return cor_slef_angle;
}

double ang_trans(double a)
{
  double correct_angle;
    if(a > 180 && a <= 360)
    {
        correct_angle = a - 360;
    }
    return correct_angle;
}

/**
 * gps��imu�����˲��õ�yaw
 * @param a
 * @param b
 * @param alpha
 * @return
 */
float ComplementaryFilter(float a, float b, float alpha) {
    // alpha ���˲�ϵ������Χ��0��1֮��
    // alpha Խ�ӽ� 1��a ��Ӱ��Խ��
    // alpha Խ�ӽ� 0��b ��Ӱ��Խ��
  float i;
  i = alpha * a + (1 - alpha) * b;
    return i;
}

float a;

void turn_angle(float angle)
{
    if(angle >= 15)
    {
        a = (float)user_steer_pid_control(SERVO_MOTOR_RMAX);
        
        Steer_set(a);
    }
    else if(angle <= -15)
    {
        a = (float)user_steer_pid_control(SERVO_MOTOR_LMAX);
        
        Steer_set(a);
    }
    else if(angle > -15 && angle <15)
    {
        a = (float)user_steer_pid_control(SERVO_MOTOR_MID + (int)angle);
        
        Steer_set(a);
    }
}