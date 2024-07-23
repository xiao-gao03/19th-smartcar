/*
 * IMU.c
 *
 *  Created on: 2023年3月18日
 *      Author: ORRN
 */


#include "zf_common_headfile.h"


//gyro_Offset_Init()--1.当陀螺仪静止的时候，会产生零飘，那么我们将静止时刻的零飘值进行均值滤波，采集一千次累加之后求其平均值，得到零飘的平均值，在后续的处理中减去零飘平均值即可
//IMU_GetValues()-----2，函数中对加速度计进行一阶低通滤波，但实际没有用到加速度计/陀螺仪减去零飘平均值并转换为弧度制
//IMU_YAW_integral()--3.对转换为弧度制后的角速度求积分，然后利用GPS函数里的弧度制转角度制函数并累积，放在定时器里，2ms中断一次，IMU刷新频率200HZ,5ms一次

gyro_param_t Gyro_Offset;//陀螺仪零飘结构体
IMU_param_t  IMU_Data;   //减去零飘数据结构体

float gyro_Offset_flag;
float Daty_X=0;//积分后的角度
float Daty_Y=0;
float Daty_Z=0;
float IMU_Daty_Z=0;
float GPS_Daty_Z=0;
float GPS_IMU_Daty_Z=0;//经过互补滤波计算出的航向角
float X;
float T_M=0;
float plus_T_M=0;  //0-360
float T_N=0;
float C_Direction_2=0;
int    direction_count;//GPS累加循环数
int    Flag=0;
int    GL_IMU_Flag=0;
double gps_direction_average;//gps计算后的平均值
double gps_direction_sum;//gps偏航角累加值
/**
 * @brief 陀螺仪零漂初始化
 * 通过采集一定数据求均值计算陀螺仪零点偏移值。
 * 后续 陀螺仪读取的数据 - 零飘值，即可去除零点偏移量。
 */
float IMU_gyro_Offset_Init()
{
    gyro_Offset_flag=0;

    Gyro_Offset.Xdata = 0;
    Gyro_Offset.Ydata = 0;
    Gyro_Offset.Zdata = 0;

    IMU_Data.gyro_x = 0;
    IMU_Data.gyro_y = 0;
    IMU_Data.gyro_z = 0;

    for (uint16_t i = 0; i < 1000; i++)
    {
//        Gyro_Offset.Xdata += imu660ra_gyro_x;
//        Gyro_Offset.Ydata += imu660ra_gyro_y;
//        Gyro_Offset.Zdata += imu660ra_gyro_z;

        Gyro_Offset.Xdata += imu963ra_gyro_x;
        Gyro_Offset.Ydata += imu963ra_gyro_y;
        Gyro_Offset.Zdata += imu963ra_gyro_z;
        system_delay_ms(5);   // 最大 1Khz
    }

    Gyro_Offset.Xdata /= 1000;
    Gyro_Offset.Ydata /= 1000;
    Gyro_Offset.Zdata /= 1000;

    return gyro_Offset_flag=1;
}

/**
 * @brief 将采集的数值转化为实际物理值, 并对陀螺仪进行去零漂处理
 * 加速度计初始化配置 -> 测量范围: ±8g        对应灵敏度: 4096 LSB/g
 * 陀螺仪初始化配置   -> 测量范围: ±2000 dps  对应灵敏度: 16.4 LSB/dps   (degree per second)
 * @tips: gyro = (gyro_val / 16.4) °/s = ((gyro_val / 16.4) * PI / 180) rad/s
 */
void IMU_GetValues()//将采集的数值转化为实际物理值, 并对陀螺仪进行去零漂处理
{
//2000dps:IMU660--16.4
//2000dps:IMU963--14.3

    //! 陀螺仪角速度必须转换为弧度制角速度: deg/s -> rad/s
//    IMU_Data.gyro_x = ((float) imu660ra_gyro_x - Gyro_Offset.Xdata) * PI / 180 / 16.4f;
//    IMU_Data.gyro_y = ((float) imu660ra_gyro_y - Gyro_Offset.Ydata) * PI / 180 / 16.4f;
//    IMU_Data.gyro_z = ((float) imu660ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 16.4f;

        IMU_Data.gyro_x = ((float) imu963ra_gyro_x - Gyro_Offset.Xdata) * PI / 180 / 14.3f;
        IMU_Data.gyro_y = ((float) imu963ra_gyro_y - Gyro_Offset.Ydata) * PI / 180 / 14.3f;
        IMU_Data.gyro_z = ((float) imu963ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 14.3f;

}


void IMU_YAW_integral()//对角速度进行积分
{


        IMU_GetValues();

    //    Daty_X+=RAD_TO_ANGLE(IMU_Data.gyro_x*0.005);
    //    Daty_Y+=RAD_TO_ANGLE(IMU_Data.gyro_y*0.005);
    //    if(IMU_Data.gyro_z<0.0045&&IMU_Data.gyro_z>-0.0045)
        if(IMU_Data.gyro_z<0.08&&IMU_Data.gyro_z>-0.08)//滤波
        {
            Daty_Z-=0;
            T_M-=0;
        }
        else
        {
             IMU_Handle_180();//规划为0-180和0-(-180)   Daty_Z
             IMU_Handle_360();//规划为0-360和0-(-360)   T_M
             IMU_Handle_0();  //规划为0-正无穷和0-负无穷  T_N
         }



}


void IMU_init() // IMU初始化
{
    if (imu963ra_init() != 0) // 检查IMU初始化是否成功
    {
        // 错误处理，例如打印错误信息或进入错误处理函数
        printf("IMU initialization failed!\n");
        return;
    }

    T_M = 0;
    IMU_gyro_Offset_Init(); // 陀螺仪零漂初始化
}



void GPS_direction_average()//计算GPS偏航角平均值
{
    if(1)
    {
        if(direction_count <= 20)
        {
            gps_direction_sum += gnss.direction;
            direction_count++;
        }
        gps_direction_average=(double)(gps_direction_sum/direction_count);
    }
}
void GPS_IMU_Complementary_filter()//将GPS反馈的direction(航向角)和IMU反馈的YAW(航向角)进行互补滤波
{
    if(gnss.direction>180)    //获取到GPS方位角信息
    {
        GPS_Daty_Z=gnss.direction-360;
    }
    else
    {
        GPS_Daty_Z=gnss.direction;
    }


    if(encoder>100)
    {
         GPS_IMU_Daty_Z=0.8*IMU_Daty_Z+0.2*GPS_Daty_Z;//互补滤波
         Flag=1;
         Daty_Z=GPS_IMU_Daty_Z;
    }
    else
    {
        if(Flag==1)
        {
            IMU_Daty_Z=GPS_IMU_Daty_Z;
            Flag=0;
        }

        IMU_Daty_Z-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);
        if(IMU_Daty_Z>360||IMU_Daty_Z<-360)//限制IMU的数值在0-360之间
        {
            IMU_Daty_Z=0;
        }
        Daty_Z=IMU_Daty_Z;

    }

}

void IMU_Handle_180()
{
    Daty_Z-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(积分过程)本来是逆时针为正,现在改为顺时针为正

    if((Daty_Z>0&&Daty_Z<=180)  ||   (Daty_Z<0&&Daty_Z>=(-180)))//顺时针
    {
        Daty_Z= +Daty_Z;
    }
    else if(Daty_Z>180 && Daty_Z<=360)
    {
        Daty_Z-=360;
    }
    else if(Daty_Z<(-180) && Daty_Z>=(-360))
    {
        Daty_Z+=360;
    }

}


void IMU_Handle_360()
{
    T_M-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(积分过程)本来是逆时针为正,现在改为顺时针为正

    if(T_M>360||T_M<-360)//限制IMU的数值在0-360之间
    {
        T_M=0;
    }
}

void IMU_Handle_0()
{
    T_N-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(积分过程)本来是逆时针为正,现在改为顺时针为正

}





// #define Ka 0.90  //加速度解算权重
// #define dt 0.005 //采样间隔（单位：秒）

// #define ANGLE_APPROX_COEFF 0 //航向角逼近系数

// #define OFFSET_COUNT 200 //零漂测定数据量

// IMU IMU_Data_two;
// float FOCF(float acc_m,float gyro_m,float* last_angle){
//     float temp_angle;
//     temp_angle=Ka*acc_m+(1-Ka)*(*last_angle+gyro_m*dt);//角速度对采样间隔积分加上上次解算角度即为从陀螺仪中推出的角度
//     *last_angle=temp_angle;
//     return temp_angle;
// }

// /* @fn IMU_update
//  * @brief 在定时器中姿态解算
//  * @param void
//  * @return void
//  */
// void IMU_update(){
//     //数据处理
//     IMU_Data_two.Roll_a=atan2(imu963ra_acc_x,imu963ra_acc_z)/(PI/180);//ax除以az再求反正切函数即为从加速度计中推出的角度
//     IMU_Data_two.Pitch_a=atan2(imu963ra_acc_y,imu963ra_acc_z)/(PI/180);
//     IMU_Data_two.Roll_g=-(imu963ra_gyro_y)/14.3;//从陀螺仪中推出的角速度，14.3根据陀螺仪量程所得
//     IMU_Data_two.Pitch_g=-(imu963ra_gyro_x)/14.3;
    
//     //一阶互补滤波
//     IMU_Data_two.Roll=FOCF(IMU_Data_two.Roll_a,IMU_Data_two.Roll_g,&IMU_Data_two.lastRoll);
//     IMU_Data_two.Pitch=FOCF(IMU_Data_two.Pitch_a,IMU_Data_two.Pitch_g,&IMU_Data_two.lastPitch);

//     IMU_Data_two.Yaw+=-(imu963ra_gyro_z)/14.3*dt;
//     //Yaw角修正
//     if(IMU_Data_two.Yaw<gnss.direction){
//         IMU_Data_two.Yaw+=ANGLE_APPROX_COEFF;
//     }
//     else if(IMU_Data_two.Yaw>gnss.direction){
//         IMU_Data_two.Yaw-=ANGLE_APPROX_COEFF;
//     }
// }

// //陀螺仪去零漂
// void IMU_offset(){
    
//     IMU_Data_two.Yaw = 0;

//     IMU_Data_two.offset_gx = 0;
//     IMU_Data_two.offset_gy = 0;
//     IMU_Data_two.offset_gz = 0;

//     for(int i=0;i<OFFSET_COUNT;i++){
//         system_delay_ms(5);
//         if(imu963ra_gyro_x==imu963ra_gyro_y){
//             i--;
//         }
//         else{
//             IMU_Data_two.offset_gx+=imu963ra_gyro_x;
//             IMU_Data_two.offset_gy+=imu963ra_gyro_y;
//             IMU_Data_two.offset_gz+=imu963ra_gyro_z;
//         }
//     }
//     IMU_Data_two.offset_gx/=OFFSET_COUNT;
//     IMU_Data_two.offset_gy/=OFFSET_COUNT;
//     IMU_Data_two.offset_gz/=OFFSET_COUNT;
// }


// float temp ;
// void IMU_get_data(){
//     imu963ra_get_acc();// 获取 IMU963RA 的加速度测量值
//     imu963ra_get_gyro();// 获取 IMU963RA 的角速度测量值

//     temp = ((float) imu963ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 14.3f;

//      if(temp<0.08&&temp>-0.08)//滤波
//         {
//             imu963ra_gyro_x-=IMU_Data_two.offset_gx;
//             imu963ra_gyro_y-=IMU_Data_two.offset_gy;
//             imu963ra_gyro_z-=IMU_Data_two.offset_gz;
//         }
    
// }


