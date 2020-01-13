#ifndef __LCD1602_H
#define __LCD1602_H

#include "Sys.h"

#define LCD1602_DB  P0      //data bus ��������

sbit LCD1602_RS = P3^5;
sbit LCD1602_RW = P3^6;
sbit LCD1602_EN = P3^4;	 

void Read_Busy();           //æ��⺯�����ж�bit7��0������ִ�У�1��ֹ
void Lcd1602_Write_Cmd(unsigned char cmd);     //д����
void Lcd1602_Write_Data(unsigned char dat);   //д����
void LcdSetCursor(unsigned char x,unsigned char y);   //��������
void DisplayOneChar (uchar X,uchar Y,uchar DData); // дһ���ֽ�
void DisplayOneStr (uchar X,uchar Y,uchar DData);//��ʾһ���ֽ��ַ�
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //��ʾ�ַ���
void InitLcd1602();              //1602��ʼ��

#endif