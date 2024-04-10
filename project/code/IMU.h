#ifndef __IMU_H__
#define __IMU_H__

//�ṹ������
typedef struct{
    float Xdata;   //��Ʈ����X
    float Ydata;   //��Ʈ����Y
    float Zdata;   //��Ʈ����Z
}gyro_param_t ;

typedef struct{
    float acc_x;   //x����ٶ�
    float acc_y;   //y����ٶ�
    float acc_z;   //z����ٶ�

    float gyro_x;  //x����ٶ�
    float gyro_y;  //y����ٶ�
    float gyro_z;  //z����ٶ�
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

 