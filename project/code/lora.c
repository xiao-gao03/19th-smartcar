/**
 * @file lora.c
 * @author xiaonan
 * @brief 
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "zf_common_headfile.h"
#include <string.h>

uint8_t number[4];
uint8_t witch_one;
uint8 data = 0;
/**
 * 串口初始化
 */
void lora_init(void)
{
    uart_init(UART_2,115200,UART2_TX_P10_1,UART2_RX_P10_0);
    uart_init(UART_3,9600,UART3_TX_P17_2,UART3_RX_P17_1);
}

/**
 * 遥控接收函数
 */
void lora_receive()
{
    uart_query_byte(UART_3,&data);
    if(data == 0x31)
    {
        data = 0x00;
        pwm_all_channel_close();
    }

}

/**
 * 裁判系统数据接收
 */
void LQ_lora()
{
    uint8_t Dat;
    uart_query_byte(UART_2,&Dat);
    if(Dat == 0x66)
    {
        for(int i = 0; i < 4;i++)
        {
            number[i] = Dat;
            uart_query_byte(UART_2,&Dat);
        }

    }

    if(number[0] == 0x66 )
    {
        switch (number[1])
        {
            case 0x01: witch_one = 1;
                break;
            case 0x02: witch_one = 2;
                break;
            case 0x03: witch_one = 3;
                break;
            case 0x04: witch_one = 4;
                break;
            case 0x05: witch_one = 5;
                break;
            case 0x06: witch_one = 6;
                break;
            case 0x07: witch_one = 7;
                break;
            case 0x08: witch_one = 8;
                break;
            default:
                break;
        }
    }
}

