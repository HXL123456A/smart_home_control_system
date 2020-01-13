#ifndef __PCF8591_H
#define __PCF8591_H

#include "Sys.h"

#define PCF8591_ADDR	0x90		//PCF8591地址
#define DACOUT_EN		0x40		//DAC输出使能


bit DAC_OUT(uchar DAT);//DAC输出
bit ADC_Read(uchar CON);//读AD数据

#endif