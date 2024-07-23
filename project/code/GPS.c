#include "zf_common_headfile.h"
#include "flash_demo.h"

#define GPS_OFFSET 10
#define GPS_GETNUM 5

void GPS_Init()
{
    gnss_init(TAU1201);
}

float points_wei[5];
float points_jing[5];
int i =0;
int j = 0;
float car_local_jing;
float car_local_wei;
int gps_get_ok = 0;
int gps_count = 0;

void gps_getpoint()
{
    
    if(key1_flag == 1 && switch1_flag == 0)         //踩点
    {

        gps_average_pointing(&points_wei[i],&points_jing[i]);       //gps获取平均点  10s
        //points_wei[i] = car_local_wei;
        //points_jing[i] = car_local_jing;
        i++;
        if(i >= 5)
        {
            i = 0;
        }
    }

    if(key3_flag == 1)              //flash写入
    {
        flashwrite(1,points_jing,5);
        flashwrite(2,points_wei,5);
        
    }

    if(key4_flag == 1)              //flash读取
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

    double local_latitude_total=0;
    double local_longitude_total=0;


void car_average(float* local_jing, float* local_wei)
{
    if(gps_count < 5)
    {
        gps_get_ok = 0;
        gnss_data_parse();
        if(!gnss.state){
        }
        else{
            
            local_latitude_total+=gnss.latitude;
            local_longitude_total+=gnss.longitude;
            gps_count++;
        }
    } 
    
    if(gps_count >= 5)
    {
        *local_wei=local_latitude_total/GPS_GETNUM;
        *local_jing=local_longitude_total/GPS_GETNUM;

        gps_count = 0;
        gps_get_ok = 1;
        local_latitude_total=0;
        local_longitude_total=0;
    }
    

}