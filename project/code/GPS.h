#ifndef __GPS_H__
#define __GPS_G__


extern double gps_angle , gps_distence;
extern double points_wei[8],points_jing[8];
void gps_getpoint();
void gps_ang_dis(double latitude, double longitude,double angle, double  dis);
void GPS_Init();

#endif
