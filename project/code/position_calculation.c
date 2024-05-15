#include "zf_common_headfile.h"


int Control_FLAG=1;         //该标志位意义是，当它为1时是无控模式(靠GPS+IMU导航)/当手柄上的按键按下时，该标志位被清0,无法执行无控模式，转入有控模式
int S_Point=0;              //停止点位参数
int P_Distance=0;           //点位距离参数
int next_point=0;           //下一个目标点
int Point_interval=0;       //点位区间数
int ZT_FLAG=0;              //绕锥桶一周标志位
int Distance_FLAG=0;        //距离切换标志位
int Angle_FLAG=0;           //角度切换标志位
int IMU_suppression_FLAG=1; //IMU抑制开启标志位
int16 SPEED_Value=0;        //目标速度
int j;



double distance=0;    //两点的距离
double azimuth=0;     //方位角(得出的函数返回值为double)
double last_azimuth=0;//上一次的方位角
double Error=0;       //方位角和航向角的误差(得出的函数返回值为double)

float  PD_YAW=0;



//***************************************************************************************
                       /*运动逻辑，待讨论*/
//***************************************************************************************


/*TODO:添加循迹模块代码
        1.调取小车目前的角度
        2.调取gps获得的目标的经纬度
        3.计算目标经纬度与正北方向的夹角
        4.计算目前角度与目标角度的差值，?∝
        5.计算舵机所需转向的角度
        
        PS：如果在正后方+-60°就倒车
            同样采取以上方法计算所需转向角度，但反向转向*/

void turn_angle()
{
    float car_target_angle;
    car_target_angle = get_two_points_azimuth(gnss.latitude,gnss.longitude,GPS_GET_LAT[j],GPS_GET_LOT[j]);
}