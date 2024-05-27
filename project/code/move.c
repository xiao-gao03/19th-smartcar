//
// Created by 28487 on 2024/5/21.
//
/**
 * 出发点  122.515877  37.165589
 * 一号点  122.515352  37.166223
 * 二号点  122.516414  37.166291
 * 三号点  122.515614  37.166341
 */


#include "zf_common_headfile.h"
#include "move.h"

double target_jing,target_wei;  //目标点的经纬度
double car_target_angle;     //小车和目标点之间的方位角
double cor_car_target_angle;//修正后小车和目标点之间的方位角
double car_target_dis;      //小车和姆比熬点之间的距离
float car_direction;

void car_move()
{
    //car_ang_trans(angle);      //得到自身角度0~+-180
    if(gnss.state == 1 && encoder > 100)
    {
      ComplementaryFilter(gnss.direction,Daty_Z,0.65,&car_direction);//gps和陀螺仪互补滤波
    }
    else{
        car_direction = Daty_Z;
    }

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
    //gps_ang_dis(target_wei,target_jing,car_target_angle,car_target_dis);
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,target_wei,target_jing);
    car_target_dis = get_two_points_distance(gnss.latitude,gnss.longitude,target_wei,target_jing);
    //角度转换 0~+-180
    cor_car_target_angle = ang_trans(car_target_angle);


    //距离目标大于一米用gps方位角转向，小于一米用硅麦转向//舵机转向
    if(car_target_dis > 1)
    {
        turn_angle(cor_car_target_angle - car_direction);
    }
    else if(car_target_dis <= 1)
    {
        turn_angle(g_Angle);
    }

    //TODO：速度后期可调
    if(car_target_dis >= 50)            //距离目标50米开外，占空比50
    {
        motor_run(1,3000);
    }
    else if(car_target_dis >=20 && car_target_dis <50)      //距离目标20-50米，占空比30
    {
        motor_run(1,2000);
    }
    else if(car_target_dis < 20)            //距离目标小于20米，占空比10
    {
        motor_run(1,1000);
    }


    //电机运动

}