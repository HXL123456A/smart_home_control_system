#ifndef __DS1302_H
#define __DS1302_H

#include "Sys.h"

sbit TSCLK = P1^0; //时钟
sbit TIO = P1^1;   //数据
sbit TRST = P1^2;  //使能

#define MAIN_Fosc		11059200UL	//宏定义主时钟HZ
#define DS1302_W_ADDR 0x80  //写时钟日历寄存器起始地址
#define DS1302_R_ADDR 0x81	//读时钟日历寄存器起始地址


void Set_DS1302_Time(uchar addr);
void Read_DS1302_Time(uchar addr);
uchar Dat_Chg_BCD(uchar dat);//10进制数据转BCD
uchar BCD_Chg_Dat(uchar dat);//BCD转10进制数据

#endif