#ifndef __DS1302_H
#define __DS1302_H

#include "Sys.h"

sbit TSCLK = P1^0; //ʱ��
sbit TIO = P1^1;   //����
sbit TRST = P1^2;  //ʹ��

#define MAIN_Fosc		11059200UL	//�궨����ʱ��HZ
#define DS1302_W_ADDR 0x80  //дʱ�������Ĵ�����ʼ��ַ
#define DS1302_R_ADDR 0x81	//��ʱ�������Ĵ�����ʼ��ַ


void Set_DS1302_Time(uchar addr);
void Read_DS1302_Time(uchar addr);
uchar Dat_Chg_BCD(uchar dat);//10��������תBCD
uchar BCD_Chg_Dat(uchar dat);//BCDת10��������

#endif