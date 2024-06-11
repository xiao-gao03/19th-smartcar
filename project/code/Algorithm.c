#include "zf_common_headfile.h"

LowPassFilter mese_filter;

float updateLowPassFilter(LowPassFilter* filter, float input) {
    // һ�׵�ͨ�˲�����ʽ: y[n] = alpha * x[n] + (1 - alpha) * y[n-1]
    float output = filter->alpha * input + (1.0f - filter->alpha) * filter->prevOutput;
    filter->prevOutput = output; // ������һ�����ֵ
    return output;
}


// ��ʼ����ͨ�˲���
void initLowPassFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->prevOutput = 0.0f; // ��ʼ���ֵΪ0
}
//================================================================pid===============================================
#include <stdio.h>
#include <stdlib.h>//�õ�rand()����
#include "time.h"

PID pid;
steer_PID steer_pid;

double measured_value = 0;//��ǰֵ
double steer_measured_value = 80;//��ǰֵ

double control_signal;
double steer_control_signal;

double dt = 1.0;  // ʱ����
double steer_dt = 0.5;  // ʱ����

// PID��ʼ������
void PID_Init(PID *pid, double kp, double ki, double kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0;
    pid->prev_error = 0.0;
    pid->output = 0.0;
}

// PID���㺯��
double PID_Compute(PID *pid, double measured_value, double dt, double setpoint) {
    
    pid->setpoint = setpoint;
    double error = pid->setpoint - measured_value;
    pid->integral += error * dt;
    double derivative = (error - pid->prev_error) / dt;
    pid->output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;
    pid->prev_error = error;
    return pid->output;
}



double user_pid_control(double speed)
{
    control_signal = PID_Compute(&pid, measured_value, dt,speed);
    // ���¹��̱������˴�������̱���������źŵļ����Թ�ϵ��
    measured_value += control_signal * dt;
    if(measured_value > 3000)
    {
      measured_value = 3000;
    }
    else if(measured_value < 0)
    {
      measured_value = 0;
    }
    
    return measured_value;
}

//===============================================================���pid===================================================

void steer_PID_Init(steer_PID *steer_pid, double kp, double ki, double kd) {
    steer_pid->kp = kp;
    steer_pid->ki = ki;
    steer_pid->kd = kd;

    steer_pid->integral = 0.0;
    steer_pid->prev_error = 0.0;
    steer_pid->output = 0.0;
}

// PID���㺯��
double steer_PID_Compute(steer_PID *steer_pid, double steer_measured_value, double dt, double setpoint) {
    
    steer_pid->setpoint = setpoint;
    double error = steer_pid->setpoint - steer_measured_value;
    steer_pid->integral += error * dt;
    double derivative = (error - steer_pid->prev_error) / dt;
    steer_pid->output = steer_pid->kp * error + steer_pid->ki * steer_pid->integral + steer_pid->kd * derivative;
    steer_pid->prev_error = error;
    return steer_pid->output;
}



double user_steer_pid_control(double angle)
{
    steer_control_signal = steer_PID_Compute(&steer_pid, steer_measured_value, steer_dt,angle);
    // ���¹��̱������˴�������̱���������źŵļ����Թ�ϵ��
    steer_measured_value += steer_control_signal * steer_dt;
    
    if(steer_measured_value>SERVO_MOTOR_RMAX)
    {
      steer_measured_value = SERVO_MOTOR_RMAX;
    }
    else if(steer_measured_value < SERVO_MOTOR_LMAX)
    {
      steer_measured_value = SERVO_MOTOR_LMAX;
    }
    
    return steer_measured_value;
}