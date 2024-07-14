/*
 * IMU.h
 *
 *  Created on: 2023��3��18��
 *      Author: ORRN
 */

#ifndef CODE_IMU_H_
#define CODE_IMU_H_

typedef struct{
    float Roll;//�������ýǶ�
    float Pitch;
    float Yaw;

    float Roll_a;//���ٶȼ���õ��ĽǶ�
    float Pitch_a;
    float Roll_g;//�����Ǽ���õ��Ľ��ٶ�
    float Pitch_g;

    float lastRoll;//�ϴεĽ���Ƕ�
    float lastPitch;

    int offset_gx;//��������Ưֵ
    int offset_gy;
    int offset_gz;
}IMU;


extern IMU IMU_Data_two;
void IMU_update();
void IMU_offset();
void IMU_get_data();




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

//ȫ�ֱ�������
extern float gyro_Offset_flag;
extern float Daty_Z;
extern float T_M;
extern float T_N;
extern int   GL_IMU_Flag;
extern double gps_direction_average;//gps������ƽ��ֵ
extern float  plus_T_M;

//��������

float IMU_gyro_Offset_Init();//��������Ư��ʼ��
void  GPS_IMU_Complementary_filter(void);//��GPS������direction(�����)��IMU������YAW(�����)���л����˲�
void  IMU_GetValues();//���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����
void  IMU_YAW_integral(void);//�Խ��ٶȽ��л���
void  IMU_init(void);//IMU��ʼ��
void  IMU_Handle_180(void);
void  IMU_Handle_360(void);
void  IMU_Handle_0  (void);

#endif /* CODE_IMU_H_ */
