#ifndef __DS18B20_H
#define __DS18B20_H

#include "Sys.h"


sbit ds = P2^2;

void dsInit();//�����߳�ʼ��ʱ��
void dsWait();//��ʱ37.95us �ȴ�18B20���ش����ź�
bit readBit();//��һλ����
unsigned char readByte();//��һ���ֽ�����
void writeByte(unsigned char dat);//дһ���ֽ�����
void sendChangeCmd();//�����¶�ת������
void sendReadCmd();//���Ͷ�����
int getTmpValue();//��ȡ�¶�
void displayTemp(int v);//��LCD1602��ʾ�¶�

#endif