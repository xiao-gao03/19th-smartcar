#ifndef __IMU_H__
#define __IMU_H__

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

extern float gyro_Offset_flag;
extern float Daty_Z;


float IMU_gyro_Offset_Init();
void IMU_GetValues();
void IMU_YAW_integral();
void IMU_init();
void IMU_Handle_180();
void IMU_Handle_360();
void IMU_Handle_0();
void IMU_SHOW();


#endif

