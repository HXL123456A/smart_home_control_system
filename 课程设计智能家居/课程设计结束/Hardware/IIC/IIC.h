#ifndef __IIC_H
#define __IIC_H

#include "Sys.h"

#define AT24C02_ADDR  0xa0	//AT24C02��ַ

/*I2C IO�ڶ���*/
sbit SDA = P2^0;
sbit SCL = P2^1;


void I2C_init();//I2C��ʼ��
void I2C_Start();/*I2C��ʼ�ź�*/
void I2C_Stop();/*I2C��ֹ�ź�*/
void Master_ACK(bit i);/*��������Ӧ��*/
bit Test_ACK();/*���ӻ�Ӧ��*/
void I2C_send_byte(uchar byte);/*����һ���ֽ�*/
uchar I2C_read_byte();/*I2C ��һ�ֽ�*/
bit I2C_TransmitData(uchar ADDR, uchar DAT);//I2C��������
uchar I2C_ReceiveData(uchar ADDR);//I2C��������


#endif