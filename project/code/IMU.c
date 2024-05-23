#include "zf_common_headfile.h"
#include "pose.h"

float acc_x = 0 , acc_y = 0 , acc_z = -980.0f;
float gyro_x = 0, gyro_y = 0, gyro_z = 0;
float mag_x = 0, mag_y = 0, mag_z = 0;
float yaw;

Pose_Module pose;
void IMU_init()
{
    imu963ra_init();

    initPose_Module(&pose);

    //连接接口
    pose.interface.data.a_x = &acc_x;
    pose.interface.data.a_y = &acc_y;
    pose.interface.data.a_z = &acc_z;
    pose.interface.data.g_x = &gyro_x;
    pose.interface.data.g_y = &gyro_y;
    pose.interface.data.g_z = &gyro_z;
    pose.interface.data.m_x = &mag_x;
    pose.interface.data.m_y = &mag_y;
    pose.interface.data.m_z = &mag_z;
}

/**
 * 获取偏航角
 * @param yaw 得到的偏航角
 */
void IMU_getangle(float *yaw)
{
    imu963ra_get_acc();                                                     // 获取 imu963ra 的加速度测量数值
    imu963ra_get_gyro();                                                    // 获取 imu963ra 的角速度测量数值
    imu963ra_get_mag();                                                     // 获取 IMU963RA 的地磁计测量数值

    acc_x = imu963ra_acc_transition(imu963ra_acc_x)*100;
    acc_y = imu963ra_acc_transition(imu963ra_acc_y)*100;
    acc_z = imu963ra_acc_transition(imu963ra_acc_z)*100;
    gyro_x = imu963ra_gyro_transition(imu963ra_gyro_x);
    gyro_y = imu963ra_gyro_transition(imu963ra_gyro_y);
    gyro_z = imu963ra_gyro_transition(imu963ra_gyro_z);
    mag_x = imu963ra_mag_transition(imu963ra_mag_x);
    mag_y = imu963ra_mag_transition(imu963ra_mag_y);
    mag_z = imu963ra_mag_transition(imu963ra_mag_z);

    calculatePose_Module(&pose, 0.005f);

    *yaw = pose.data.yaw;
}