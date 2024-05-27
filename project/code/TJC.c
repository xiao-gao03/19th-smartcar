//
// Created by 28487 on 2024/5/25.
//

#include "zf_common_headfile.h"

char tjcstr[100];

void TJC_START()
{
    TJC_Sendbit(0xff);
}

void TJC_init()
{
    uart_init(UART_3,115200,UART3_TX_P17_2,UART3_RX_P17_1);
    TJC_START();
}

void TJC_Sendbit(uint8_t bit) {
    uint8_t i;
    for (i = 0; i < 3; i++) {
        if (bit != 0) {
            uart_write_byte(UART_3, bit);  //发送一个字节
        } else {
            return;
        }
    }
}

void TJC_Send(char *buf1)
{
    if(buf1 != 0){
        uart_write_string(UART_3,buf1);
    }else{
        return ;
    }
}

void TJC_messageSend()
{
    sprintf(tjcstr,"IMU.t1.txt=\"imu角度:%.0f\"",Daty_Z);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"MESE.t1.txt=\"硅麦角度:%.0f\"",g_Angle);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t1.txt=\"经度:%f\"",gnss.longitude);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t4.txt=\"维度:%f\"",gnss.latitude);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t2.txt=\"角:%f\"",gnss.direction);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t5.txt=\"速度:%f\"",gnss.speed);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t3.txt=\"目距:%f\"",car_target_dis);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t6.txt=\"目角:%.0f\"",car_target_angle);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS.t7.txt=\"成功否:%d\"",gnss.state);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t1.txt=\"1经%f\"",points_jing[0]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t5.txt=\"1维:%f\"",points_wei[0]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t2.txt=\"2经:%f\"",points_jing[1]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t6.txt=\"2维:%f\"",points_wei[1]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t3.txt=\"3经:%f\"",points_jing[2]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t7.txt=\"3维:%f\"",points_wei[2]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t4.txt=\"4经:%f\"",points_jing[3]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"GPS2.t8.txt=\"4维:%f\"",points_wei[3]);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"all.t1.txt=\"第几个:%d\"",witch_one);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);


}
