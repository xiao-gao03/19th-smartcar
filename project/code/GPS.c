#include "zf_common_headfile.h"


void GPS_Init()
{
    gnss_init(TAU1201);
}

double points_wei[8];
double points_jing[8];
int i =0;
int j = 0;

void gps_getpoint()
{
        

    if(key1_flag == 1 && switch1_flag == 0 && switch2_flag == 0)
    {
        points_wei[i] = gnss.latitude;
        points_jing[i] = gnss.longitude;
        i++;
        j++;
        if(i >= 8)
        {
            i = 0;
        }
        if(j>8)
        {
            j = 0;
        }
    }
}