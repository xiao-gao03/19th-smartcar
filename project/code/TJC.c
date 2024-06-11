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
            uart_write_byte(UART_3, bit);  //����һ���ֽ�
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
    sprintf(tjcstr,"main.t0.txt=\"IMU:%f\"",plus_T_M); //0-360
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t1.txt=\"%.0f\"",mic_angle);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t2.txt=\"��Ŀ��:%.0f\"",car_target_angle);  //0-360
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t3.txt=\"�ɵ���:%d\"",i);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t4.txt=\"����:%f\"",car_target_dis);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);
    
    sprintf(tjcstr,"main.t5.txt=\"��:%f\"",gnss.longitude);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);
    
    sprintf(tjcstr,"main.t6.txt=\"γ:%f\"",gnss.latitude);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t9.txt=\"spd:%d\"",encoder);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

    sprintf(tjcstr,"main.t10.txt=\"Ӧ�ս�:%.0f\"",my_beta);
    TJC_Send(tjcstr);
    TJC_Sendbit(0xff);

}
