/*
 * Algorithm.h
 *
 *  Created on: 2023年3月19日
 *      Author: ORRN
 */

#ifndef __ALGORITHM_H___
#define __ALGORITHM_H___

typedef struct {
    float alpha; // 滤波器系数
    float prevOutput; // 上一个输出值
} LowPassFilter;

extern LowPassFilter mese_filter;

extern double steer_dt;

void initLowPassFilter(LowPassFilter* filter, float alpha);
float updateLowPassFilter(LowPassFilter* filter, float input);


typedef struct {
    double kp;   // 比例系数
    double ki;   // 积分系数
    double kd;   // 微分系数
    double setpoint;  // 目标值
    double integral;  // 积分误差
    double prev_error;  // 前一时刻的误差
    double output;  // 输出值
} PID;

typedef struct {
    double kp;   // 比例系数
    double ki;   // 积分系数
    double kd;   // 微分系数
    double setpoint;  // 目标值
    double integral;  // 积分误差
    double prev_error;  // 前一时刻的误差
    double output;  // 输出值
} steer_PID;

extern PID pid;
extern steer_PID steer_pid;

void PID_Init(PID *pid, double kp, double ki, double kd);
double PID_Compute(PID *pid, double measured_value, double dt, double setpoint);
double user_pid_control(double speed);

void steer_PID_Init(steer_PID *pid, double kp, double ki, double kd);
double steer_PID_Compute(steer_PID *pid, double measured_value, double dt, double setpoint);
double user_steer_pid_control(double angle);

#endif /* CODE_ALGORITHM_H_ */
