#ifndef __SYS_H
#define __SYS_H

#define uchar unsigned char
#define uint unsigned int

#include <reg52.h>
#include "Delay.h"
#include "Key.h"
#include "InfraRed.h"
#include "Secret.h"
#include <intrins.h>
#include "LCD1602.h"
#include <string.h>


sbit DUAN=P2^6;
sbit WEI=P2^7;
sbit Beep=P2^3;



#endif