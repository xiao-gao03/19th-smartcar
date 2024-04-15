#ifndef __POSITION_CALCULATION_H__
#define __POSITION_CALCULATION_H__


//全局变量声明
extern int S_Point;
extern int P_Distance;
extern int Control_FLAG;         //该标志位意义是，当它为1时是无控模式(靠GPS+IMU导航)/当手柄上的按键按下时，该标志位被清0,无法执行无控模式，转入有控模式
extern double Error;
extern int   STEER_Value;
extern int16 SPEED_Value;
extern double azimuth;
extern int next_point;



#endif