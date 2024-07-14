#include "stdio.h"

double measured_value = 0;//��ǰֵ
double steer_measured_value = 80;//��ǰֵ

double control_signal;
double steer_control_signal;

double dt = 1.0;  // ʱ����
double steer_dt = 0.5;  // ʱ����

typedef struct {
    double kp;   // ����ϵ��
    double ki;   // ����ϵ��
    double kd;   // ΢��ϵ��
    double setpoint;  // Ŀ��ֵ
    double integral;  // �������
    double prev_error;  // ǰһʱ�̵����
    double output;  // ���ֵ
} PID;

PID pid;

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


int main()
{
    int a;
    PID_Init(&pid, 0.1, 0.00, 0.01);
    a = user_pid_control(2000);
    printf("%d")

}