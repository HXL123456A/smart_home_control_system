#ifndef __DS18B20_H
#define __DS18B20_H

#include "Sys.h"


sbit ds = P2^2;

void dsInit();//单总线初始化时序
void dsWait();//延时37.95us 等待18B20发回存在信号
bit readBit();//读一位数据
unsigned char readByte();//读一个字节数据
void writeByte(unsigned char dat);//写一个字节数据
void sendChangeCmd();//发送温度转换命令
void sendReadCmd();//发送读命令
int getTmpValue();//获取温度
void displayTemp(int v);//用LCD1602显示温度

#endif