#ifndef __POSITION_CALCULATION_H__
#define __POSITION_CALCULATION_H__

extern double angle;

double car_ang_trans(double angle0);
double ang_trans(double a);
void turn_angle(double angle);
void ComplementaryFilter(float a, float b, float alpha,float *angle);

#endif