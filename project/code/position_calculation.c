#include "zf_common_headfile.h"

double angle;
double SERVO_angle;
//***************************************************************************************
                       /*运动逻辑，待讨论*/
//***************************************************************************************


/*TODO:添加循迹模块代码
        1.调取小车目前的角度
        2.调取gps获得的目标的经纬度
        3.计算目标经纬度与正北方向的夹角
        4.计算目前角度与目标角度的差值，?∝
        5.计算舵机所需转向的角度
        
        PS：如果在正后方+-60°就倒车
            同样采取以上方法计算所需转向角度，但反向转向*/
/**
 * 自身方位角转换函数，将gps的360°转化到0-180
 * @param angle 得到的角度
 */
void car_ang_trans(double angle0)
{
    if(angle0 > 180 && angle0 <= 360)
    {
        angle0 = angle0 - 180;
    }
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
 * gps和imu互补滤波得到yaw
 * @param a
 * @param b
 * @param alpha
 * @return
 */
void ComplementaryFilter(float a, float b, float alpha,float *angle) {
    // alpha 是滤波系数，范围在0到1之间
    // alpha 越接近 1，a 的影响越大
    // alpha 越接近 0，b 的影响越大
    *angle = alpha * a + (1 - alpha) * b;
}

void turn_angle(double angle)
{
    if(angle >= 15)
    {
        Steer_set(SERVO_MOTOR_RMAX);
    }
    else if(angle <= -15)
    {
        Steer_set(SERVO_MOTOR_LMAX);
    }
    else if(angle > -15 && angle <15)
    {
        Steer_set(SERVO_MOTOR_MID + angle);
    }
}