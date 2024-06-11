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
#include "arm_math.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技 CMSIS-DAP 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 P14_0
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 P14_1
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源

// ***************************** 例程测试说明 *****************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用逐飞助手打开对应的串口，串口波特率为 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在逐飞助手上看到如下串口信息：
// fft count use time: 876 us
//
// ifft count use time: 964 us
// 5.可以在逐飞助手的示波器界面看到FFT运算完成后的结果波形
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************

             

float inputSignal_1[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
float fft_outputSignal_1[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

float inputSignal_2[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
float fft_outputSignal_2[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

float inputSignal_3[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
float fft_outputSignal_3[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

float inputSignal_0[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
float fft_outputSignal_0[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

int adc_flag = 0;
int p = 0;

uint32 fft_count_time_us  = 0;
uint32 ifft_count_time_us = 0;
arm_cfft_instance_f32 arm_cfft_instance_f32_len_2048;                       // 定义FFT对象

extern int adc_flag;

    // **************************** 信号预处理 ****************************
//    for(int i = 0; i < FFT_SIZE; i++){
//        // 对输入数据虚拟赋值，这里模拟输入一个500hz的正弦波信号
//        // 实际声音信号由ADC采集
//        // 将输入信号填入实部，虚部为0(FFT计算使用复数，float数组的复数存储方式为实部虚部交替存储)
//        inputSignal[2 * i] = /*adc_convert(ADC0_CH00_P06_0);*/ arm_sin_f32(FFT_DEMO_PI * i / 10);
//        inputSignal[2*i + 1] = 0;
//    }    
    // **************************** 信号预处理 ****************************
    
void FFT_Init()
{          
    arm_cfft_init_f32(&arm_cfft_instance_f32_len_2048, FFT_SIZE);               // 初始化FFT对象 赋予计算长度   
    // adc_init(ADC0_CH00_P06_0,ADC_12BIT);
    // pit_us_init(PIT_CH0,100);
}
    // **************************** 初始化内容 ****************************
    
    
    // ************************** 计算结果输出 *************************** 
    
    
    // ****************************** 总结 ******************************* 
    // 可以通过逐飞助手的示波器观察到FFT计算结果中，在数组下标为 103 的位置的值最大，此时反推模拟的输入信号频率
    // 采样频率为10khz，FFT计算长度为2048个数据，那么FFT频率点则为 10000 除以 2048 等于 4.8828125 hz，意味着FFT计算结果的间隔为4.8828125 hz
    // 因此数组下标为 103 的位置的频率则是 103 * 4.8828125 = 502.9296875 hz，此时可以大概得出原信号频率(没有准确计算出来500hz是因为有计算精度误差)
    // ****************************** 总结 ******************************* 

void FFT_comp()
{
  if(adc_flag == 1)
    {

      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_0 , 0 , 1);        // 32位浮点FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_1 , 0 , 1);        // 32位浮点FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_2 , 0 , 1);        // 32位浮点FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_3 , 0 , 1);        // 32位浮点FFT运算(运算结果将替换原inputSignal的内容)

      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_0 , FFT_SIZE);               // 将FFT结果转换为幅度谱(转换幅度谱是为了观察波形)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_1 , FFT_SIZE);               // 将FFT结果转换为幅度谱(转换幅度谱是为了观察波形)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_2 , FFT_SIZE);               // 将FFT结果转换为幅度谱(转换幅度谱是为了观察波形)
      arm_cmplx_mag_f32(inputSignal_1 , fft_outputSignal_3 , FFT_SIZE);               // 将FFT结果转换为幅度谱(转换幅度谱是为了观察波形)

      for(int i = 0; i < FFT_SIZE; i++)
      {
        if(i*4.8828125 < 1699 || i*4.8828125 > 1704)
        {
          fft_outputSignal_0[i] = 0;
          fft_outputSignal_1[i] = 0;
          fft_outputSignal_2[i] = 0;
          fft_outputSignal_3[i] = 0;
        }
      }

      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_0 , 1 , 1);        // 32位浮点逆FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_1 , 1 , 1);        // 32位浮点逆FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_2 , 1 , 1);        // 32位浮点逆FFT运算(运算结果将替换原inputSignal的内容)
      arm_cfft_f32(&arm_cfft_instance_f32_len_2048 , inputSignal_3 , 1 , 1);        // 32位浮点逆FFT运算(运算结果将替换原inputSignal的内容)
      
//      for(int i = 0; i < FFT_SIZE; i++)
//      {
//          printf("%f,%f,\t%f,\t\t%f,\t%f,\t%f,\t%f,\t%f,\t%f\n",fft_outputSignal_0[i],inputSignal_0[i * 2],fft_outputSignal_1[i],inputSignal_1[i * 2],fft_outputSignal_2[i],inputSignal_2[i * 2],fft_outputSignal_3[i],inputSignal_3[i * 2],i*4.8828125);
//        
//      }   
      
//        printf("\r\n fft count use time: %d us\r\n",   fft_count_time_us);          // 输出FFT运算耗时
//        printf("\r\n ifft count use time: %d us\r\n", ifft_count_time_us);          // 输出逆FFT运算耗时
//      adc_flag =0;
    }
}


void FFT_capture()
{
    if(adc_flag == 0)
    {
      if(p < FFT_SIZE)
      {
        inputSignal_0[2 * p] = adc_convert(ADC0_CH00_P06_0);
        inputSignal_0[2*p + 1] = 0;

        inputSignal_1[2 * p] = adc_convert(ADC0_CH01_P06_1);
        inputSignal_1[2*p + 1] = 0;

        inputSignal_2[2 * p] = adc_convert(ADC0_CH02_P06_2);
        inputSignal_2[2*p + 1] = 0;

        inputSignal_3[2 * p] = adc_convert(ADC0_CH03_P06_3);
        inputSignal_3[2*p + 1] = 0;
        p++;
      }
      else if(p >= FFT_SIZE)
      {
        adc_flag = 1;
      }
    }
}
      

