/*
 * IMU.c
 *
 *  Created on: 2023��3��18��
 *      Author: ORRN
 */


#include "zf_common_headfile.h"


//gyro_Offset_Init()--1.�������Ǿ�ֹ��ʱ�򣬻������Ʈ����ô���ǽ���ֹʱ�̵���Ʈֵ���о�ֵ�˲����ɼ�һǧ���ۼ�֮������ƽ��ֵ���õ���Ʈ��ƽ��ֵ���ں����Ĵ����м�ȥ��Ʈƽ��ֵ����
//IMU_GetValues()-----2�������жԼ��ٶȼƽ���һ�׵�ͨ�˲�����ʵ��û���õ����ٶȼ�/�����Ǽ�ȥ��Ʈƽ��ֵ��ת��Ϊ������
//IMU_YAW_integral()--3.��ת��Ϊ�����ƺ�Ľ��ٶ�����֣�Ȼ������GPS������Ļ�����ת�Ƕ��ƺ������ۻ������ڶ�ʱ���2ms�ж�һ�Σ�IMUˢ��Ƶ��200HZ,5msһ��

gyro_param_t Gyro_Offset;//��������Ʈ�ṹ��
IMU_param_t  IMU_Data;   //��ȥ��Ʈ���ݽṹ��

float gyro_Offset_flag;
float Daty_X=0;//���ֺ�ĽǶ�
float Daty_Y=0;
float Daty_Z=0;
float IMU_Daty_Z=0;
float GPS_Daty_Z=0;
float GPS_IMU_Daty_Z=0;//���������˲�������ĺ����
float X;
float T_M=0;
float plus_T_M=0;  //0-360
float T_N=0;
float C_Direction_2=0;
int    direction_count;//GPS�ۼ�ѭ����
int    Flag=0;
int    GL_IMU_Flag=0;
double gps_direction_average;//gps������ƽ��ֵ
double gps_direction_sum;//gpsƫ�����ۼ�ֵ
/**
 * @brief ��������Ư��ʼ��
 * ͨ���ɼ�һ���������ֵ�������������ƫ��ֵ��
 * ���� �����Ƕ�ȡ������ - ��Ʈֵ������ȥ�����ƫ������
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
        system_delay_ms(5);   // ��� 1Khz
    }

    Gyro_Offset.Xdata /= 1000;
    Gyro_Offset.Ydata /= 1000;
    Gyro_Offset.Zdata /= 1000;

    return gyro_Offset_flag=1;
}

/**
 * @brief ���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����
 * ���ٶȼƳ�ʼ������ -> ������Χ: ��8g        ��Ӧ������: 4096 LSB/g
 * �����ǳ�ʼ������   -> ������Χ: ��2000 dps  ��Ӧ������: 16.4 LSB/dps   (degree per second)
 * @tips: gyro = (gyro_val / 16.4) ��/s = ((gyro_val / 16.4) * PI / 180) rad/s
 */
void IMU_GetValues()//���ɼ�����ֵת��Ϊʵ������ֵ, ���������ǽ���ȥ��Ư����
{
//2000dps:IMU660--16.4
//2000dps:IMU963--14.3

    //! �����ǽ��ٶȱ���ת��Ϊ�����ƽ��ٶ�: deg/s -> rad/s
//    IMU_Data.gyro_x = ((float) imu660ra_gyro_x - Gyro_Offset.Xdata) * PI / 180 / 16.4f;
//    IMU_Data.gyro_y = ((float) imu660ra_gyro_y - Gyro_Offset.Ydata) * PI / 180 / 16.4f;
//    IMU_Data.gyro_z = ((float) imu660ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 16.4f;

        IMU_Data.gyro_x = ((float) imu963ra_gyro_x - Gyro_Offset.Xdata) * PI / 180 / 14.3f;
        IMU_Data.gyro_y = ((float) imu963ra_gyro_y - Gyro_Offset.Ydata) * PI / 180 / 14.3f;
        IMU_Data.gyro_z = ((float) imu963ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 14.3f;

}


void IMU_YAW_integral()//�Խ��ٶȽ��л���
{


        IMU_GetValues();

    //    Daty_X+=RAD_TO_ANGLE(IMU_Data.gyro_x*0.005);
    //    Daty_Y+=RAD_TO_ANGLE(IMU_Data.gyro_y*0.005);
    //    if(IMU_Data.gyro_z<0.0045&&IMU_Data.gyro_z>-0.0045)
        if(IMU_Data.gyro_z<0.08&&IMU_Data.gyro_z>-0.08)//�˲�
        {
            Daty_Z-=0;
            T_M-=0;
        }
        else
        {
             IMU_Handle_180();//�滮Ϊ0-180��0-(-180)   Daty_Z
             IMU_Handle_360();//�滮Ϊ0-360��0-(-360)   T_M
             IMU_Handle_0();  //�滮Ϊ0-�������0-������  T_N
         }



}


void IMU_init() // IMU��ʼ��
{
    if (imu963ra_init() != 0) // ���IMU��ʼ���Ƿ�ɹ�
    {
        // �����������ӡ������Ϣ������������
        printf("IMU initialization failed!\n");
        return;
    }

    T_M = 0;
    IMU_gyro_Offset_Init(); // ��������Ư��ʼ��
}



void GPS_direction_average()//����GPSƫ����ƽ��ֵ
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
void GPS_IMU_Complementary_filter()//��GPS������direction(�����)��IMU������YAW(�����)���л����˲�
{
    if(gnss.direction>180)    //��ȡ��GPS��λ����Ϣ
    {
        GPS_Daty_Z=gnss.direction-360;
    }
    else
    {
        GPS_Daty_Z=gnss.direction;
    }


    if(encoder>100)
    {
         GPS_IMU_Daty_Z=0.8*IMU_Daty_Z+0.2*GPS_Daty_Z;//�����˲�
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
        if(IMU_Daty_Z>360||IMU_Daty_Z<-360)//����IMU����ֵ��0-360֮��
        {
            IMU_Daty_Z=0;
        }
        Daty_Z=IMU_Daty_Z;

    }

}

void IMU_Handle_180()
{
    Daty_Z-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(���ֹ���)��������ʱ��Ϊ��,���ڸ�Ϊ˳ʱ��Ϊ��

    if((Daty_Z>0&&Daty_Z<=180)  ||   (Daty_Z<0&&Daty_Z>=(-180)))//˳ʱ��
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
    T_M-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(���ֹ���)��������ʱ��Ϊ��,���ڸ�Ϊ˳ʱ��Ϊ��

    if(T_M>360||T_M<-360)//����IMU����ֵ��0-360֮��
    {
        T_M=0;
    }
}

void IMU_Handle_0()
{
    T_N-=RAD_TO_ANGLE(IMU_Data.gyro_z*0.005);//(���ֹ���)��������ʱ��Ϊ��,���ڸ�Ϊ˳ʱ��Ϊ��

}





// #define Ka 0.90  //���ٶȽ���Ȩ��
// #define dt 0.005 //�����������λ���룩

// #define ANGLE_APPROX_COEFF 0 //����Ǳƽ�ϵ��

// #define OFFSET_COUNT 200 //��Ư�ⶨ������

// IMU IMU_Data_two;
// float FOCF(float acc_m,float gyro_m,float* last_angle){
//     float temp_angle;
//     temp_angle=Ka*acc_m+(1-Ka)*(*last_angle+gyro_m*dt);//���ٶȶԲ���������ּ����ϴν���Ƕȼ�Ϊ�����������Ƴ��ĽǶ�
//     *last_angle=temp_angle;
//     return temp_angle;
// }

// /* @fn IMU_update
//  * @brief �ڶ�ʱ������̬����
//  * @param void
//  * @return void
//  */
// void IMU_update(){
//     //���ݴ���
//     IMU_Data_two.Roll_a=atan2(imu963ra_acc_x,imu963ra_acc_z)/(PI/180);//ax����az�������к�����Ϊ�Ӽ��ٶȼ����Ƴ��ĽǶ�
//     IMU_Data_two.Pitch_a=atan2(imu963ra_acc_y,imu963ra_acc_z)/(PI/180);
//     IMU_Data_two.Roll_g=-(imu963ra_gyro_y)/14.3;//�����������Ƴ��Ľ��ٶȣ�14.3������������������
//     IMU_Data_two.Pitch_g=-(imu963ra_gyro_x)/14.3;
    
//     //һ�׻����˲�
//     IMU_Data_two.Roll=FOCF(IMU_Data_two.Roll_a,IMU_Data_two.Roll_g,&IMU_Data_two.lastRoll);
//     IMU_Data_two.Pitch=FOCF(IMU_Data_two.Pitch_a,IMU_Data_two.Pitch_g,&IMU_Data_two.lastPitch);

//     IMU_Data_two.Yaw+=-(imu963ra_gyro_z)/14.3*dt;
//     //Yaw������
//     if(IMU_Data_two.Yaw<gnss.direction){
//         IMU_Data_two.Yaw+=ANGLE_APPROX_COEFF;
//     }
//     else if(IMU_Data_two.Yaw>gnss.direction){
//         IMU_Data_two.Yaw-=ANGLE_APPROX_COEFF;
//     }
// }

// //������ȥ��Ư
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
//     imu963ra_get_acc();// ��ȡ IMU963RA �ļ��ٶȲ���ֵ
//     imu963ra_get_gyro();// ��ȡ IMU963RA �Ľ��ٶȲ���ֵ

//     temp = ((float) imu963ra_gyro_z - Gyro_Offset.Zdata) * PI / 180 / 14.3f;

//      if(temp<0.08&&temp>-0.08)//�˲�
//         {
//             imu963ra_gyro_x-=IMU_Data_two.offset_gx;
//             imu963ra_gyro_y-=IMU_Data_two.offset_gy;
//             imu963ra_gyro_z-=IMU_Data_two.offset_gz;
//         }
    
// }


