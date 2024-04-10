#include "zf_common_headfile.h"

gyro_param_t Gyro_Offset;//��������Ʈ�ṹ��
IMU_param_t  IMU_Data;   //��ȥ��Ʈ���ݽṹ��

float Daty_Z=0;
float T_M=0;
float T_N=0;

float  gyro_Offset_flag = 0;

/**
 * @brief ��������Ư��ʼ��
 * ͨ���ɼ�һ���������ֵ�������������ƫ��ֵ��
 * ���� �����Ƕ�ȡ������ - ��Ʈֵ������ȥ�����ƫ������
 */
float IMU_gyro_Offset_Init()
{
    Gyro_Offset.Xdata = 0;
    Gyro_Offset.Ydata = 0;
    Gyro_Offset.Zdata = 0;
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
        if(IMU_Data.gyro_z<0.015&&IMU_Data.gyro_z>-0.015)//�˲�
        {
            Daty_Z-=0;

        }
        else
        {
             IMU_Handle_180();//�滮Ϊ0-180��0-(-180)   Daty_Z
             IMU_Handle_360();//�滮Ϊ0-360��0-(-360)   T_M
             IMU_Handle_0();  //�滮Ϊ0-�������0-������  T_N
         }



}


void IMU_init()//IMU��ʼ��
{

//    imu660ra_init();   //IMU660�ߵ���ʼ��
    imu963ra_init();   //IMU660�ߵ���ʼ��
    pit_ms_init(PIT_CH0, 5);                              // (IMU)��ʼ�� CCU60_CH0 Ϊ�����ж� 5ms ����,IMU660Ƶ��Ϊ200HZ
    IMU_gyro_Offset_Init();// ��������Ư��ʼ��

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

void IMU_SHOW()
{
	printf("yaw: %f \n",Daty_Z);
}
