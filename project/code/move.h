//
// Created by 28487 on 2024/5/21.
//

#ifndef __MOVE_H__
#define __MOVE_H__


extern float target_jing,target_wei;  //目标点的经纬度
extern float car_target_angle;     //小车和目标点之间的方位角
extern float cor_car_target_angle;//修正后小车和目标点之间的方位角
extern double car_target_dis;      //小车和目标点之间的距离
extern float car_direction;
extern float cor_self_a;

void car_move();

#endif