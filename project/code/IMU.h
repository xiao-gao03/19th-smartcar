#ifndef __IMU_H__
#define __IMU_H__

extern float acc_x  , acc_y , acc_z ;
extern float gyro_x , gyro_y , gyro_z ;
extern float mag_x , mag_y , mag_z ;
extern float yaw;

void IMU_init();
void IMU_getangle(float *yaw);

#endif
