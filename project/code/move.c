//
// Created by 28487 on 2024/5/21.
//

#include "zf_common_headfile.h"
#include "move.h"

double target_jing,target_wei;  //Ŀ���ľ�γ��
double car_target_angle;     //С����Ŀ���֮��ķ�λ��
double car_target_dis;      //С����ķ�Ȱ���֮��ľ���
float car_direction;

void move()
{
    car_ang_trans(angle);      //�õ�����Ƕ�0~+-180

    ComplementaryFilter(angle,yaw,0.6,car_direction);//gps�������ǻ����˲�

    switch(witch_one)               //Ŀ��㸳ֵ
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

    //�õ�С����Ŀ���ķ�λ�Ǻ;���
    gps_ang_dis(target_wei,target_jing,&car_target_angle,&car_target_dis);

    //�Ƕ�ת�� 0~+-180
    ang_trans(car_target_angle);
    ang_trans(g_Angle);

    //����Ŀ�����һ����gps��λ��ת��С��һ���ù���ת��//���ת��
    if(car_target_dis > 1)
    {
        turn_angle(car_target_angle);
    }
    else if(car_target_dis <= 1)
    {
        turn_angle(g_Angle);
    }






    //����˶�

}