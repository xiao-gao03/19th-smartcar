#ifndef __IMU_H__
#define __IMU_H__

typedef struct{
    float Xdata;   //x轴角度
    float Ydata;   //Y轴角度
    float Zdata;   //Z轴角度
}gyro_param_t ;

typedef struct{
    float acc_x;   //x角速度数值
    float acc_y;   //y角速度数值
    float acc_z;   //z角速度数值

    float gyro_x;  //x加速度数值
    float gyro_y;  //y加速度数值
    float gyro_z;  //z加速度数值
}IMU_param_t ;

extern float gyro_Offset_flag;
extern float Data_Z;
extern float T_M_Z;
extern float T_N_Z;
extern int GL_IMU_Flag;


float IMU_gyro_Offset_Init();
void IMU_GetValues();
void IMU_YAW_integral();
void IMU_init();
void IMU_Handle_180();
void IMU_Handle_360();
void IMU_Handle_0();
void IMU_SHOW();


#endif

 