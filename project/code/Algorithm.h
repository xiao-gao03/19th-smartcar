/*
 * Algorithm.h
 *
 *  Created on: 2023��3��19��
 *      Author: ORRN
 */

#ifndef __ALGORITHM_H___
#define __ALGORITHM_H___

typedef struct {
    float alpha; // �˲���ϵ��
    float prevOutput; // ��һ�����ֵ
} LowPassFilter;

extern LowPassFilter mese_filter;

extern double steer_dt;

void initLowPassFilter(LowPassFilter* filter, float alpha);
float updateLowPassFilter(LowPassFilter* filter, float input);


typedef struct {
    double kp;   // ����ϵ��
    double ki;   // ����ϵ��
    double kd;   // ΢��ϵ��
    double setpoint;  // Ŀ��ֵ
    double integral;  // �������
    double prev_error;  // ǰһʱ�̵����
    double output;  // ���ֵ
} PID;

typedef struct {
    double kp;   // ����ϵ��
    double ki;   // ����ϵ��
    double kd;   // ΢��ϵ��
    double setpoint;  // Ŀ��ֵ
    double integral;  // �������
    double prev_error;  // ǰһʱ�̵����
    double output;  // ���ֵ
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
