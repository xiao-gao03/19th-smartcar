#include "zf_common_headfile.h"


int Control_FLAG=1;         //�ñ�־λ�����ǣ�����Ϊ1ʱ���޿�ģʽ(��GPS+IMU����)/���ֱ��ϵİ�������ʱ���ñ�־λ����0,�޷�ִ���޿�ģʽ��ת���п�ģʽ
int S_Point=0;              //ֹͣ��λ����
int P_Distance=0;           //��λ�������
int next_point=0;           //��һ��Ŀ���
int Point_interval=0;       //��λ������
int ZT_FLAG=0;              //��׶Ͱһ�ܱ�־λ
int Distance_FLAG=0;        //�����л���־λ
int Angle_FLAG=0;           //�Ƕ��л���־λ
int IMU_suppression_FLAG=1; //IMU���ƿ�����־λ
int16 SPEED_Value=0;        //Ŀ���ٶ�
int j;



double distance=0;    //����ľ���
double azimuth=0;     //��λ��(�ó��ĺ�������ֵΪdouble)
double last_azimuth=0;//��һ�εķ�λ��
double Error=0;       //��λ�Ǻͺ���ǵ����(�ó��ĺ�������ֵΪdouble)

float  PD_YAW=0;



//***************************************************************************************
                       /*�˶��߼���������*/
//***************************************************************************************


/*TODO:���ѭ��ģ�����
        1.��ȡС��Ŀǰ�ĽǶ�
        2.��ȡgps��õ�Ŀ��ľ�γ��
        3.����Ŀ�꾭γ������������ļн�
        4.����Ŀǰ�Ƕ���Ŀ��ǶȵĲ�ֵ��?��
        5.����������ת��ĽǶ�
        
        PS�����������+-60��͵���
            ͬ����ȡ���Ϸ�����������ת��Ƕȣ�������ת��*/

void turn_angle()
{
    float car_target_angle;
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,GPS_GET_LAT[j],GPS_GET_LOT[j]);
}