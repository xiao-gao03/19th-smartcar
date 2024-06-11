#ifndef __FFT_H__
#define __FFT_H__


#define FFT_SIZE        (2048 )                  // FFT数据大小
#define SAMPLING_FREQ   (10000)                  // 信号采样频率
#define FFT_DEMO_PI     (3.1415926) 

extern float inputSignal_1[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
extern float fft_outputSignal_1[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

extern float inputSignal_2[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
extern float fft_outputSignal_2[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

extern float inputSignal_3[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
extern float fft_outputSignal_3[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2

extern float inputSignal_0[FFT_SIZE * 2];                // 定义输入信号 输入信号为复数 所以长度为 FFT_SIZE * 2
extern float fft_outputSignal_0[FFT_SIZE * 2];           // 定义FFT输出信号 输出信号为复数 所以长度为 FFT_SIZE * 2
extern int adc_flag;
extern int p;

void FFT_Init();
void FFT_comp();
void FFT_capture();

#endif
