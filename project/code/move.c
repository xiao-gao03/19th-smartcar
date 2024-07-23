//
// Created by 28487 on 2024/5/21.
//
/**
 * ??????  122.515877  37.165589
 * ????  122.515352  37.166223
 * ?????  122.516414  37.166291
 * ?????  122.515614  37.166341
 * 122.509837  37.169730
 */


#include "zf_common_headfile.h"
#include "move.h"

int room = 0;

float target_jing,target_wei;  
float car_target_angle;     
float cor_car_target_angle;
double car_target_dis;      
float car_direction;
float cor_self_a;

int back_flag=0;
int tar_speed = 0,last_tar_speed = 0;

void car_move()
{

   if(T_M >= 0)
   {
       plus_T_M=T_M;
   }
   else if (T_M < 0)
   {
       plus_T_M = 360 + T_M;
   }

   car_direction = plus_T_M;

    switch(witch_one)               //�ж���һ���ű��ڹ���
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
    
    //???????????
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,target_wei,target_jing);
    car_target_dis = get_two_points_distance(gnss.latitude,gnss.longitude,target_wei,target_jing);



  if(room == 0)                           //�ж��Ƿ�Ϊ����
  {
    if(car_target_dis > 1)
    {
      turn_f();                         //gpsת��  
    }
    else if(car_target_dis <= 1)
    {
        turn_angle(-mic_angle);             //����Ƕ�ת
      //turn_angle(-mic_angle);
    }

    if(witch_one != 0)
    {
      if(my_alpha <= 30 || my_alpha >= -30)      //��Ŀ������30��
      {
        if(car_target_dis >= 20)            //����Ŀ��50������
        {
          steer_dt = 1.0;
          if( my_alpha > 30 || my_alpha < -30)
          {
            motor_run(1,800);
          }
          else
          {
            motor_run(1,3000);
          }
          
         // tar_speed = 2000;

        }
        else if(car_target_dis >=10 && car_target_dis <20)      //����Ŀ��20-50��
        {
          steer_dt = 1.0;
  //          BLDC_Cloop_ctrl(1,700);
           if( my_alpha > 30 || my_alpha < -30)
          {
            motor_run(1,800);
          }
          else
          {
            motor_run(1,2800);
          }
         // motor_run(1,2300);
          //tar_speed = 2000;
        }
        else if(car_target_dis < 10 && car_target_dis > 5)            //����Ŀ��5-20��
        {
          steer_dt = 1.0;
  //          BLDC_Cloop_ctrl(1,2000);
           if( my_alpha > 30 || my_alpha < -30)
          {
            motor_run(1,800);
          }
          else
          {
            motor_run(1,800);
          }
         // motor_run(1,800);
          //tar_speed = 2000;
        }
      }
      
      if(car_target_dis <= 5)        //����Ŀ���������Ŀ��ǶȲ����
      {
        //steer_dt = 2.0;
      //BLDC_Cloop_ctrl(1,500); 
        if(back_flag == 1)
        {
            motor_run(0,500);
        }
        else 
        {
          motor_run(1,500);
        }
          
        
       // tar_speed = 800;
      }
    }
    else if(witch_one == 0)
    {
      motor_run(1,0);
      //tar_speed = 0;
    }


//    if(tar_speed >= last_tar_speed)//�ж��ٶ��Ƿ�������
//    {
//      BLDC_Cloop_ctrl(1,tar_speed);
//    }
//    else
//    {
//      motor_run(1,tar_speed);
//    }

    //last_tar_speed = tar_speed;  //��������
  }


  else if(room == 1)                       //�ж��Ƿ�Ϊ����
  {
    if(witch_one != 0)
    {
      turn_angle(-mic_angle);
      motor_run(1,1000);
    }
    else if(witch_one == 0)
    {
      motor_run(1,0);
    }
  }
}