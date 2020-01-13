#include "Sys.h"


void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}

//将例程中按键扫描修改，先扫描行，再扫描列，不然会与LCD1602冲突

uchar KeyScan()	//带返回值的子函数
{
	uchar KeyValue=22;
	P3 = 0x0f;//判断哪一行被按下
	if(P3 != 0x0f)
	{
		delay(5);//软件消抖
		if( P3 != 0x0f)
		{
			switch(P3)
			{
				case 0x0e:	KeyValue = 0;	break;
				case 0x0d:	KeyValue = 4;	break;
				case 0x0b:	KeyValue = 8;	break;
				case 0x07:	KeyValue = 12;	break;
			}
			P3 = 0xf0;//判断哪一列被按下
			switch(P3)
			{
				case 0xe0:	KeyValue = KeyValue;	break;
				case 0xd0:	KeyValue += 1;	break;
				case 0xb0:	KeyValue += 2;	break;
				case 0x70:	KeyValue += 3;	break;
			}
			while(P3 != 0xf0);//松手检测
		}			
	}
	
	P3 = 0xff;//判断独立按键
	if(P3 != 0xff)
	{
		delay(5);//软件消抖
		if( P3 != 0xff)
		{
			switch(P3)
			{
				case 0xfe:	KeyValue = 16;	break;
				case 0xfd:	KeyValue = 17;	break;
				case 0xfb:	KeyValue = 18;	break;
				case 0xf7:	KeyValue = 19;	break;
			}
			while(P3 != 0xff);//松手检测
		}	
	}	
	if(KeyValue!=22&&(KeyValue>9&&KeyValue<16))//a~f,+39
	{
		KeyValue+=39;
	}
	return KeyValue;
}