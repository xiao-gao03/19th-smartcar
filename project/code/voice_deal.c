#include "voice_deal.h"
#include "zf_common_typedef.h"
#include "zf_common_headfile.h"
//#include "butterworth.h"
#include "arm_math.h"

#define sample_point 2048
#define MIC_RAW_DATA_LEN  2500

int16 FB[3];
int16 LR[3];
int16 SUM_delay12 = 0;
int16 SUM_delay34 = 0;

int16 mic_raw_data[4][MIC_RAW_DATA_LEN];
int16 mic_raw_data_count;
int16 mic_raw_data_count_save;

float mic_angle=0.0;

int16 Mic1_fftIn[sample_point];//麦克风Mic1参与FFT的时域输入数组
int16 Mic2_fftIn[sample_point];//麦克风Mic2参与FFT的时域输入数组
int16 Mic3_fftIn[sample_point];//麦克风Mic3参与FFT的时域输入数组
int16 Mic4_fftIn[sample_point];//麦克风Mic4参与FFT的时域输入数组
          
int32 ADC[4]={0,0,0,0};

/*********************************************************
 ********************* 核心函数 **************************
 ********************************************************/

void Mic_init(void)
{
  adc_init (MIC_PIN1, ADC_12BIT);
  adc_init (MIC_PIN2, ADC_12BIT);
  adc_init (MIC_PIN3, ADC_12BIT);
  adc_init (MIC_PIN4, ADC_12BIT);
  //pit_us_init(PIT_CH1,100);
}

void mic_data_get(void)
{   
    ADC[0]=mic_raw_data[0][mic_raw_data_count]=adc_convert(MIC_PIN1)-1885;
    ADC[1]=mic_raw_data[1][mic_raw_data_count]=adc_convert(MIC_PIN2)-1862;
    ADC[2]=mic_raw_data[2][mic_raw_data_count]=adc_convert(MIC_PIN3)-1892;
    ADC[3]=mic_raw_data[3][mic_raw_data_count]=adc_convert(MIC_PIN4)-1872;
    mic_raw_data_count++;
    
    if(mic_raw_data_count>=2500)
    {
      mic_raw_data_count=0;
    } 
}

//函数简介          复制硅麦数据（最近的 FFT_SIZE个）
//参数说明          void
//返回参数          void
//使用示例          mic data_ copy()
//备注信息          取出循环数组最近的2048个数据用于互相关计算

void mic_data_copy(void)
{
    uint16 mic_raw_data_count_temp = 0;
    uint16 mic_data_count = 0;
    
    mic_raw_data_count_save = mic_raw_data_count;              //保存当前时刻的采集位置（mic_raw_ data_count 会在中断被持续更新，保存以防止数据异常）

    if (mic_raw_data_count_save < sample_point)                     //若当前采集位置小于需复制的长度（无法一个循环完成复制），则分为两端分别复制数据
    {
        mic_raw_data_count_temp = MIC_RAW_DATA_LEN- (sample_point - mic_raw_data_count_save);
          
        for(int16 i = mic_raw_data_count_temp;i<MIC_RAW_DATA_LEN;i++)
        {
            Mic1_fftIn[mic_data_count]=mic_raw_data[0][i];         //保存用于FFT计算的数据 实部赋值
            Mic2_fftIn[mic_data_count]=mic_raw_data[1][i];
            Mic3_fftIn[mic_data_count]=mic_raw_data[2][i];
            Mic4_fftIn[mic_data_count]=mic_raw_data[3][i]; 
            mic_data_count++;
        } 

        for(int16 i =0;i<mic_raw_data_count_save;i++)
        {
            Mic1_fftIn[mic_data_count]=mic_raw_data[0][i];         //保存用于FFT计算的数据 实部赋值
            Mic2_fftIn[mic_data_count]=mic_raw_data[1][i];
            Mic3_fftIn[mic_data_count]=mic_raw_data[2][i];
            Mic4_fftIn[mic_data_count]=mic_raw_data[3][i];
            mic_data_count++;
        }
    }
    else
    {
        for(int16 i= 0;i<sample_point;i++)
        {
            Mic1_fftIn[i]=mic_raw_data[0][i];         //保存用于FFT计算的数据 实部赋值
            Mic2_fftIn[i]=mic_raw_data[1][i];
            Mic3_fftIn[i]=mic_raw_data[2][i];
            Mic4_fftIn[i]=mic_raw_data[3][i];
        } 
    }
}


void Mic_Process(void)//中位值滤波取中间值
{
    int i=0;
    int16 a1=0,a2=0,a3=0,b1=0,b2=0,b3=0,FB_Temp=0,LR_Temp=0;
    for(i=0;i<3;i++)
    {   
      mic_data_copy();
      FB[i]=Micdata_cov(Mic3_fftIn,Mic1_fftIn,sample_point,-9,9,1);
      LR[i]=Micdata_cov(Mic4_fftIn,Mic2_fftIn,sample_point,-9,9,1);
    }
    a1=FB[0]; a2=FB[1]; a3=FB[2];
    b1=LR[0]; b2=LR[1]; b3=LR[2];
    if ( a1<a2 ) { FB_Temp=a1;a1=a2;a2=FB_Temp; }
    if ( a1<a3 ) { FB_Temp=a1;a1=a3;a3=FB_Temp; }
    if ( a2<a3 ) { FB_Temp=a2;a2=a3;a3=FB_Temp; }
    SUM_delay34=a2;
    if ( b1<b2 ) { LR_Temp=b1;b1=b2;b2=LR_Temp; }
    if ( b1<b3 ) { LR_Temp=b1;b1=b3;b3=LR_Temp; }
    if ( b2<b3 ) { LR_Temp=b2;b2=b3;b3=LR_Temp; }
    SUM_delay12=b2;
    mic_angle=atan2(SUM_delay12,SUM_delay34)/PI*180;
}


int16 Micdata_cov(int16* data1, int16* data2, unsigned short point, short point1, short point2, unsigned short step) {
    int8 cnt = 0;
    int32 data1val = 0;
    int32 data2val = 0;
    int32 data3val = 0;
    int16 t = 0;
    int16 pos = 0;
    int16 maxpos = 0;
    float32_t maxval = 0;
    for (cnt = point1; cnt < point2; cnt++) 
    {
        for (t = 0; t < point; t += step) 
        {
             pos = t - cnt;
             if (pos < 0) 
             {
                 pos += sample_point;
             } 
             else if (pos >= sample_point)
             {
                 pos -= sample_point;
             }
             data3val = data1[t] * data2[pos]; //互相关
             data1val = data1val + data3val;
         }
         data2val = data1val;  //防止数据溢出    右移12位 比除2048快
         if (maxval <= data2val)     //找出互相关最大值的下标，即为时延
         {
             maxpos = cnt;
             maxval = data2val;
         }
         data1val = 0;
        }
     return maxpos;//返回值即为时延
}
