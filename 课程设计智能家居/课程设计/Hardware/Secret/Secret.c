#include "Sys.h"

uchar password_original[5]={1,2,3,4,5};//‘≠√‹¬Î
uchar temp_password[5]={0,0,0,0,0};
uchar password_new[5];


void KeyAction()
{
	uchar Input=22;
	static uchar keyWei=0;
	
	Input=KeyScan();
	
	if(Input!=22&&keyWei<5)
	{
//		Lcd1602_Write_Cmd(0x01);
		Lcd1602_Write_Cmd(0x80+keyWei);
		temp_password[keyWei]=Input;
		Lcd1602_Write_Data(Input+'0');
		keyWei++;
	}
	if(Input==16)
	{
		if(make_sure()==0)
		{
			Beep=0;
		}
	}
	
}

int make_sure()
{
	unsigned char i=0;
	for(i;i<5;i++)
	{
		if(temp_password[i]!=password_original[i])
		{
			return 0;
		}
	}
	return 1;
}