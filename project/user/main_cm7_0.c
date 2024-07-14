/*********************************************************************************************************************
* CYT4BB Opensourec Library 即（ CYT4BB 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 CYT4BB 开源库的一部分
*
* CYT4BB 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main_cm7_0
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT4BB
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-1-4       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************

int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// 时钟配置及系统初始化<务必保留>
    debug_info_init();                  // 调试串口信息初始化


    //Buzzer_init();      //蜂鸣器初始化

    TJC_init();         //串口屏初始化

    Key_init();         //按键初始化
  
    Steer_init();       //舵机初始化

   

    lora_init();        //无线串口初始化

    PID_Init(&pid, 0.1, 0.00, 0.01);  // 设置比例、积分、微分系数和目标值//0.2/0.00/0.01/
    steer_PID_Init(&steer_pid,0.1,0.00,0.01);

    flash_init();

    motor_init();       //电机初始化

    Mic_init();
    
float a,b,c,d;
    //initLowPassFilter(&mese_filter,0.65);
    
 
    pit_ms_init(PIT_CH0,5);
    pit_ms_init(PIT_CH1,100);
    pit_us_init(PIT_CH2,100);  //100us进入一次中断  中断中采集adc数据
    pit_ms_init(PIT_CH10,5);
    
    
    
  // 此处编写用户代码 例如外设初始化代码等
  while (1)
  {
        key_scan();  //按键扫描  
      gps_getpoint();  //采点
      Mic_Process();
      if(key1_flag == 1)
      {
        key1_flag = 0;
      }
      
      key3_flag = 0;
      key4_flag = 0;
      if(key2_flag == 1)
      {
        IMU_init();         //陀螺仪初始化
        GPS_Init();         //gps初始化
      }
      key2_flag = 0;
      HALL_gather();
      car_move();
      
      //printf("%f\n",mic_angle);

      if(switch2_flag == 0)
      {
          TJC_messageSend();
      }

      a=adc_convert(ADC0_CH03_P06_3);
      b=adc_convert(ADC0_CH01_P06_1);
      c=adc_convert(ADC0_CH00_P06_0);
      d=adc_convert(ADC0_CH02_P06_2);
      printf("%.0f\n",T_M);
      
  }
  // 此处编写用户代码 例如外设初始化代码等
}

// **************************** 代码区域 ****************************
