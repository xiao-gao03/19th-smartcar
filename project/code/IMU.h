/*
 * IMU.h
 *
 *  Created on: 2023年3月18日
 *      Author: ORRN
 */

#ifndef CODE_IMU_H_
#define CODE_IMU_H_

typedef struct{
    float Roll;//解算所得角度
    float Pitch;
    float Yaw;

    float Roll_a;//加速度计算得到的角度
    float Pitch_a;
    float Roll_g;//陀螺仪计算得到的角速度
    float Pitch_g;

    float lastRoll;//上次的解算角度
    float lastPitch;

    int offset_gx;//陀螺仪零漂值
    int offset_gy;
    int offset_gz;
}IMU;


extern IMU IMU_Data_two;
void IMU_update();
void IMU_offset();
void IMU_get_data();




//结构体声明
typedef struct{
    float Xdata;   //零飘参数X
    float Ydata;   //零飘参数Y
    float Zdata;   //零飘参数Z
}gyro_param_t ;

typedef struct{
    float acc_x;   //x轴加速度
    float acc_y;   //y轴加速度
    float acc_z;   //z轴加速度

    float gyro_x;  //x轴角速度
    float gyro_y;  //y轴角速度
    float gyro_z;  //z轴角速度
}IMU_param_t ;

//全局变量声明
extern float gyro_Offset_flag;
extern float Daty_Z;
extern float T_M;
extern float T_N;
extern int   GL_IMU_Flag;
extern double gps_direction_average;//gps计算后的平均值
extern float  plus_T_M;

//函数声明

float IMU_gyro_Offset_Init();//陀螺仪零漂初始化
void  GPS_IMU_Complementary_filter(void);//将GPS反馈的direction(航向角)和IMU反馈的YAW(航向角)进行互补滤波
void  IMU_GetValues();//将采集的数值转化为实际物理值, 并对陀螺仪进行去零漂处理
void  IMU_YAW_integral(void);//对角速度进行积分
void  IMU_init(void);//IMU初始化
void  IMU_Handle_180(void);
void  IMU_Handle_360(void);
void  IMU_Handle_0  (void);

#endif /* CODE_IMU_H_ */
