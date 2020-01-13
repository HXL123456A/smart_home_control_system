#ifndef __INFRARED_H
#define __INFRARED_H

#include "Sys.h"


void init();//对红外通讯所使用到的外部中断0和定时器0初始化
void IRcordpro();//把提取的33次脉宽解码 NEC协议



#endif