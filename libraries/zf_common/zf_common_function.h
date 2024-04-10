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
* 文件名称          zf_common_function
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

#ifndef _zf_common_function_h_
#define _zf_common_function_h_

#include "zf_common_typedef.h"

//====================================================宏定义函数区====================================================
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     绝对值函数 数据范围是 [-32767,32767]
// 参数说明     dat             需要求绝对值的数
// 返回参数     int             返回绝对值
// 使用示例     dat = func_abs(dat);                            // 将dat变成正数
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     func_abs(x)             ((x) >= 0 ? (x): -(x))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     限幅 数据范围是 [-32768,32767]
// 参数说明     x               被限幅的数据
// 参数说明     y               限幅范围(数据会被限制在-y至+y之间)
// 返回参数     int             限幅之后的数据         
// 使用示例     int dat = func_limit(500, 300);                 // 数据被限制在-300至+300之间  因此返回的结果是300
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     func_limit(x, y)        ((x) > (y) ? (y) : ((x) < -(y) ? -(y) : (x)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     双边限幅 数据范围是 [-32768,32767]
// 参数说明     x               被限幅的数据
// 参数说明     a               限幅范围左边界
// 参数说明     b               限幅范围右边界
// 返回参数     int             限幅之后的数据         
// 使用示例     int dat = func_limit_ab(500, -300, 400);        //数据被限制在-300至+400之间  因此返回的结果是400
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     func_limit_ab(x, a, b)  ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

//====================================================宏定义函数区====================================================

//=====================================================常规函数区=====================================================
void        func_get_sin_amplitude_table        (uint32 *data_buffer, uint32 sample_max, uint32 amplitude_max, uint32 offset_degree);

uint32      func_get_greatest_common_divisor    (uint32 num1, uint32 num2);

void        func_soft_delay                     (volatile long t);

int32       func_str_to_int                     (char *str);
void        func_int_to_str                     (char *str, int32 number);
uint32      func_str_to_uint                    (char *str);
void        func_uint_to_str                    (char *str, uint32 number);
float       func_str_to_float                   (char *str);
void        func_float_to_str                   (char *str, float number, uint8 point_bit);
double      func_str_to_double                  (char *str);
void        func_double_to_str                  (char *str, double number, uint8 point_bit);
uint32      func_str_to_hex                     (char *str);
void        func_hex_to_str                     (char *str, uint32 number);

uint32      zf_sprintf                          (int8 *buff, const int8 *format, ...);
//=====================================================常规函数区=====================================================

#endif
