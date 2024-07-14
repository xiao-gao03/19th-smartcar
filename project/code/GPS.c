#include "zf_common_headfile.h"
#include "flash_demo.h"

#define GPS_OFFSET 10

void GPS_Init()
{
    gnss_init(TAU1201);
}

float points_wei[5];
float points_jing[5];
int i =0;
int j = 0;

void gps_getpoint()
{
    
    if(key1_flag == 1 && switch1_flag == 0)
    {

        gps_average_pointing(&points_wei[i],&points_jing[i]);
        // points_wei[i] = gnss.latitude;
        // points_jing[i] = gnss.longitude;
        i++;
        if(i >= 5)
        {
            i = 0;
        }
    }

    if(key3_flag == 1)
    {
        flashwrite(1,points_jing,5);
        flashwrite(2,points_wei,5);
        
    }

    if(key4_flag == 1)
    {
        flash_read(1,points_jing,5);
        flash_read(2,points_wei,5);
        
    }
}


void gps_average_pointing(float* average_latitude,float* average_longitude)
{
    double latitude_total=0;
    double longitude_total=0;
    int i=0;
    while(i<GPS_OFFSET){
        
        if(!gnss.state){
        }
        else{
            
            latitude_total+=gnss.latitude;
            longitude_total+=gnss.longitude;
            i++;
            system_delay_ms(1000);
        }
    }
    *average_latitude=latitude_total/GPS_OFFSET;
    *average_longitude=longitude_total/GPS_OFFSET;
}