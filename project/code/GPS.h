#ifndef __GPS_H__
#define __GPS_G__

extern int i;
extern float points_wei[5],points_jing[5];

extern float car_local_jing;
extern float car_local_wei;
extern int gps_get_ok;
extern int gps_count;

void gps_getpoint();
void GPS_Init();
void gps_average_pointing(float* average_latitude,float* average_longitude);
void car_average(float* local_jing, float* local_wei);

#endif
