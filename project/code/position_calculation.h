#ifndef __POSITION_CALCULATION_H__
#define __POSITION_CALCULATION_H__

extern double angle;

void car_ang_trans(double *angle0);
void ang_trans(double *angle);
void turn_angle(double angle);
void ComplementaryFilter(float a, float b, float alpha,float *angle);

#endif