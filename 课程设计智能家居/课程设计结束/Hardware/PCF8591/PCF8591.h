#ifndef __PCF8591_H
#define __PCF8591_H

#include "Sys.h"

#define PCF8591_ADDR	0x90		//PCF8591��ַ
#define DACOUT_EN		0x40		//DAC���ʹ��


bit DAC_OUT(uchar DAT);//DAC���
bit ADC_Read(uchar CON);//��AD����

#endif