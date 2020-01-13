#ifndef __SYS_H
#define __SYS_H

#define uchar unsigned char
#define uint unsigned int
#define LightOn 255
#define LightOff 0
#define FanOn 1
#define FanOff 0
#define Human 1
#define Machine 0

#include <reg52.h>
#include "Delay.h"
#include "Key.h"
#include "InfraRed.h"
#include "Secret.h"
#include <intrins.h>
#include "LCD1602.h"
#include <string.h>
#include "DS18B20.h"
#include <math.h>
#include "DS1302.h"
#include "IIC.h"
#include "PCF8591.h"
#include "ULN2003.h"

sbit DUAN=P2^6;
sbit WEI=P2^7;
sbit Beep=P2^3;



#endif