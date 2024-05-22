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

/**
 * 串口初始化
 */
void lora_init(void)
{
    uart_init(UART_2,115200,UART2_TX_P10_1,UART2_RX_P10_0);
    uart_init(UART_1,9600,UART1_TX_P04_1,UART1_RX_P04_0);
}

/**
 * 遥控接收函数
 */
void lora_receive()
{
    uint8 data;
    uart_query_byte(UART_1,&data);
    if(data == 0x31)
    {
        motor_run(1,3000);
    }
    else if(data == 0x32)
    {
        motor_stop();
    }
}

/**
 * 裁判系统数据接收
 */
void LQ_lora()
{
    uart_query_byte(UART_2,number);
    if(number[0] == 0x66)
    {
        switch (number[1])
        {
            case 0x00: witch_one = 0;
                break;
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
        }
    }
}

