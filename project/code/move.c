//
// Created by 28487 on 2024/5/21.
//
/**
 * ������  122.515877  37.165589
 * һ�ŵ�  122.515352  37.166223
 * ���ŵ�  122.516414  37.166291
 * ���ŵ�  122.515614  37.166341
 * 122.509837  37.169730
 */


#include "zf_common_headfile.h"
#include "move.h"

float target_jing,target_wei;  //Ŀ���ľ�γ��
float car_target_angle;     //С����Ŀ���֮��ķ�λ��
float cor_car_target_angle;//������С����Ŀ���֮��ķ�λ��
double car_target_dis;      //С����Ŀ���֮��ľ���
float car_direction;
float cor_self_a;

void car_move()
{
   // cor_self_a = car_ang_trans(gnss.direction);      //�õ�����Ƕ�0~+-180

   if(T_M >= 0)
   {
       plus_T_M=T_M;
   }
   else if (T_M < 0)
   {
       plus_T_M = 360 + T_M;
   }

   car_direction = plus_T_M;

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
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,target_wei,target_jing);
    car_target_dis = get_two_points_distance(gnss.latitude,gnss.longitude,target_wei,target_jing);

    //����Ŀ�����һ����gps��λ��ת��С��һ���ù���ת��//���ת��
    if(car_target_dis > 5)
    {
        turn();
    }
    else if(car_target_dis <= 5)
    {
        turn_angle(-g_Angle);
    }

    if(witch_one != 0)
    {
      //TODO���ٶȺ��ڿɵ�
      if(car_target_dis >= 50)            //����Ŀ��50�׿��⣬ռ�ձ�50
      {
          BLDC_Cloop_ctrl(1,5000);
      }
      else if(car_target_dis >=20 && car_target_dis <50)      //����Ŀ��20-50�ף�ռ�ձ�30
      {
          BLDC_Cloop_ctrl(1,3000);
      }
      else if(car_target_dis < 20)            //����Ŀ��С��20�ף�ռ�ձ�10
      {
          BLDC_Cloop_ctrl(1,1000);
      }
    }
    else if(witch_one == 0)
    {
      motor_run(1,0);
    }
    //����˶�

}