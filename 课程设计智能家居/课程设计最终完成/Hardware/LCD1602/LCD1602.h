#ifndef __LCD1602_H
#define __LCD1602_H

#include "Sys.h"

#define LCD1602_DB  P0      //data bus 数据总线

sbit LCD1602_RS = P3^5;
sbit LCD1602_RW = P3^6;
sbit LCD1602_EN = P3^4;	 

void Read_Busy();           //忙检测函数，判断bit7是0，允许执行；1禁止
void Lcd1602_Write_Cmd(unsigned char cmd);     //写命令
void Lcd1602_Write_Data(unsigned char dat);   //写数据
void LcdSetCursor(unsigned char x,unsigned char y);   //设置坐标
void DisplayOneChar (uchar X,uchar Y,uchar DData); // 写一个字节
void DisplayOneStr (uchar X,uchar Y,uchar DData);//显示一个字节字符
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //显示字符串
void InitLcd1602();              //1602初始化

#endif