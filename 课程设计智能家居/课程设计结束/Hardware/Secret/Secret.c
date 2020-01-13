#include "Sys.h"
#include <string.h>


uchar password_original[5]={1,2,3,4,5};//原密码
uchar temp_password[5]={0,0,0,0,0};


uchar chance=3;
uchar Lock=LockOn;
uint Beeptime;

extern uchar choosemode;

void KeyAction()
{
	uchar Input=22;
	static uchar keyWei=0;
	
	Input=KeyScan();
	if(Input!=22&&keyWei<5&&Input!=16&&Input!=17&&Input!=18&&Input!=19)
	{	
		temp_password[keyWei]=Input;
		DisplayOneChar(6+keyWei,1,'*');
		keyWei++;
	}
	if(Input==16)//密码确认
	{
		keyWei=0;
		if(make_sure()==0)//输入错误
		{
			LcdShowStr(6,1,"     ");
			chance--;
			Beeptime=0;
		}
		else//输入正确
		{
			keyWei=0;
			choosemode=1;
			chance=3;
			Lock=LockOff;
		}
	}
	if(Input==17)//清除
	{
		uchar i=0;
		keyWei=0;
		Lcd1602_Write_Cmd(0x80);
		for(i=0;i<5;i++)
		{
			LcdShowStr(6,1,"     ");
			temp_password[i]=0;
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

uchar changesecret()
{
	uchar Input=22;
	static uchar keyWei=0;
	Input=KeyScan();
	if(Input!=22&&keyWei<5&&Input!=16&&Input!=17&&Input!=18&&Input!=19)
	{	
		temp_password[keyWei]=Input;
		DisplayOneChar(11+keyWei,1,Input+'0');
		keyWei++;
	}
	if(Input==16&&keyWei==5)
	{
		uchar i;
		keyWei=0;
		strcpy(password_original,temp_password);
		for(i=0;i<5;i++)
		{
			temp_password[i]=0;
		}
		Lcd1602_Write_Cmd(0x01);
		for(i=1;i<6;i++)
		{
			I2C_TransmitData(i,password_original[i-1]);
			Delayms(5);
		}
		LcdShowStr(0,0,"Changed.");
		Delayms(3000);
		Lcd1602_Write_Cmd(0x01);
		choosemode=1;
		return 1;
	}
	if(Input==17)
	{
		uchar i=0;
		keyWei=0;
		Lcd1602_Write_Cmd(0x01);
		for(i=0;i<5;i++)
		{
			temp_password[i]=0;
		}
	}
	return 0;
}