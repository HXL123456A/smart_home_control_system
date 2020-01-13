#ifndef __IIC_H
#define __IIC_H

#include "Sys.h"

#define AT24C02_ADDR  0xa0	//AT24C02地址

/*I2C IO口定义*/
sbit SDA = P2^0;
sbit SCL = P2^1;


void I2C_init();//I2C初始化
void I2C_Start();/*I2C起始信号*/
void I2C_Stop();/*I2C终止信号*/
void Master_ACK(bit i);/*主机发送应答*/
bit Test_ACK();/*检测从机应答*/
void I2C_send_byte(uchar byte);/*发送一个字节*/
uchar I2C_read_byte();/*I2C 读一字节*/
bit I2C_TransmitData(uchar ADDR, uchar DAT);//I2C发送数据
uchar I2C_ReceiveData(uchar ADDR);//I2C接收数据


#endif