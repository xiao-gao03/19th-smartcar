//
// Created by 28487 on 2024/5/21.
//

#include "zf_common_headfile.h"
#include "move.h"

double target_jing,target_wei;  //目标点的经纬度
double car_target_angle;     //小车和目标点之间的方位角
double car_target_dis;      //小车和姆比熬点之间的距离
float car_direction;

void move()
{
    car_ang_trans(angle);      //得到自身角度0~+-180

    ComplementaryFilter(angle,yaw,0.6,car_direction);//gps和陀螺仪互补滤波

    switch(witch_one)               //目标点赋值
    {
        case 1:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 2:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 3:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 4:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 5:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 6:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 7:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        case 8:target_jing = points_jing[witch_one - 1]; target_wei = points_wei[witch_one - 1];
            break;
        default: break;
    }

    //得到小车和目标点的方位角和距离
    gps_ang_dis(target_wei,target_jing,&car_target_angle,&car_target_dis);

    //角度转换 0~+-180
    ang_trans(car_target_angle);
    ang_trans(g_Angle);

    //距离目标大于一米用gps方位角转向，小于一米用硅麦转向//舵机转向
    if(car_target_dis > 1)
    {
        turn_angle(car_target_angle);
    }
    else if(car_target_dis <= 1)
    {
        turn_angle(g_Angle);
    }






    //电机运动

}