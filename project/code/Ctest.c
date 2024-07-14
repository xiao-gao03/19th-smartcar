#include "stdio.h"

double measured_value = 0;//当前值
double steer_measured_value = 80;//当前值

double control_signal;
double steer_control_signal;

double dt = 1.0;  // 时间间隔
double steer_dt = 0.5;  // 时间间隔

typedef struct {
    double kp;   // 比例系数
    double ki;   // 积分系数
    double kd;   // 微分系数
    double setpoint;  // 目标值
    double integral;  // 积分误差
    double prev_error;  // 前一时刻的误差
    double output;  // 输出值
} PID;

PID pid;

// PID初始化函数
void PID_Init(PID *pid, double kp, double ki, double kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0;
    pid->prev_error = 0.0;
    pid->output = 0.0;
}

// PID计算函数
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
    // 更新过程变量（此处假设过程变量与控制信号的简单线性关系）
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


int main()
{
    int a;
    PID_Init(&pid, 0.1, 0.00, 0.01);
    a = user_pid_control(2000);
    printf("%d")

}