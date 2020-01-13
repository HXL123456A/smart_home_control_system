#include "Sys.h"


void choose(uchar i);



void main()
{
//	uchar num=22;
	uchar choosemode=0;
	DUAN=0xff;
	WEI=0x00;
	InitLcd1602();
//	Lcd1602_Write_Cmd(0x01);
//	Lcd1602_Write_Cmd(0x80);
	
	while(1)
	{
		KeyAction();
		
		
//		num=KeyScan();
//		if(num!=22)
//		{
//			Lcd1602_Write_Cmd(0x01);
//			Lcd1602_Write_Data(num+'0');
//		}
	}
}

void choose(uchar i)
{
	switch(i)
	{
		case 0:
			break;
	}
}