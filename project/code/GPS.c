#include "zf_common_headfile.h"

void GPS_Init()
{
    gnss_init(TAU1201);
}

double points_wei[8] = {37.166223,37.166291,37.166341};
double points_jing[8] = {122.515352,122.516414,122.515614};
int i =0;

void gps_getpoint()
{
    if(key1_flag == 1 && switch1_flag == 0 && switch2_flag == 0)
    {
        points_wei[i] = gnss.latitude;
        points_jing[i] = gnss.longitude;
        i++;
        if(i >= 8)
        {
            i = 0;
        }
    }
}

/**
 * ���С����Ŀ���ķ�λ�;���
 * @param latitude  Ŀ��ά��
 * @param longitude Ŀ�꾭��
 * @param angle �õ��ĽǶ�
 * @param dis  �õ����ٶ�
 */
//void gps_ang_dis(double latitude, double longitude,double angle, double  dis)
//{
//    angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,latitude,longitude);
//    dis = get_two_points_distance(gnss.latitude,gnss.longitude,latitude,longitude);
//}


