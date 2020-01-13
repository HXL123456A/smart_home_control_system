#ifndef __DS18B20_H
#define __DS18B20_H

#include "Sys.h"


sbit ds = P2^2;

void dsInit();
void dsWait();
bit readBit();
unsigned char readByte();
void writeByte(unsigned char dat);
void sendChangeCmd();
void sendReadCmd();
int getTmpValue();
void displayTemp(int v);

#endif