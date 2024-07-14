#ifndef __GPS_H__
#define __GPS_G__

extern int i;
extern float points_wei[5],points_jing[5];
void gps_getpoint();
void GPS_Init();
void gps_average_pointing(float* average_latitude,float* average_longitude);

#endif
