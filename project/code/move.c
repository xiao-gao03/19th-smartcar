//
// Created by 28487 on 2024/5/21.
//
/**
 * ������  122.515877  37.165589
 * һ�ŵ�  122.515352  37.166223
 * ���ŵ�  122.516414  37.166291
 * ���ŵ�  122.515614  37.166341
 */


#include "zf_common_headfile.h"
#include "move.h"

double target_jing,target_wei;  //Ŀ���ľ�γ��
double car_target_angle;     //С����Ŀ���֮��ķ�λ��
double cor_car_target_angle;//������С����Ŀ���֮��ķ�λ��
double car_target_dis;      //С����ķ�Ȱ���֮��ľ���
float car_direction;

void car_move()
{
    //car_ang_trans(angle);      //�õ�����Ƕ�0~+-180
    if(gnss.state == 1 && encoder > 100)
    {
      ComplementaryFilter(gnss.direction,Daty_Z,0.65,&car_direction);//gps�������ǻ����˲�
    }
    else{
        car_direction = Daty_Z;
    }

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
    //gps_ang_dis(target_wei,target_jing,car_target_angle,car_target_dis);
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,target_wei,target_jing);
    car_target_dis = get_two_points_distance(gnss.latitude,gnss.longitude,target_wei,target_jing);
    //�Ƕ�ת�� 0~+-180
    cor_car_target_angle = ang_trans(car_target_angle);


    //����Ŀ�����һ����gps��λ��ת��С��һ���ù���ת��//���ת��
    if(car_target_dis > 1)
    {
        turn_angle(cor_car_target_angle - car_direction);
    }
    else if(car_target_dis <= 1)
    {
        turn_angle(g_Angle);
    }

    //TODO���ٶȺ��ڿɵ�
    if(car_target_dis >= 50)            //����Ŀ��50�׿��⣬ռ�ձ�50
    {
        motor_run(1,3000);
    }
    else if(car_target_dis >=20 && car_target_dis <50)      //����Ŀ��20-50�ף�ռ�ձ�30
    {
        motor_run(1,2000);
    }
    else if(car_target_dis < 20)            //����Ŀ��С��20�ף�ռ�ձ�10
    {
        motor_run(1,1000);
    }


    //����˶�

}