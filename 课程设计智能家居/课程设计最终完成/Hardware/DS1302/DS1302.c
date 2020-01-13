#include "Sys.h"

//时钟日历暂存数组，秒、分、时、日、月、周、年 初值为= 16年2月15日 周1 23:58:50
uchar TimeData[7]={50, 58, 21, 15, 2, 1, 16};

void DS1302_W_Byte(uchar dat)
{
	uchar i;
	for(i = 0; i < 8; i++) //每次写1bit，写8次
	{
		TSCLK = 0;		   //拉低时钟总线
		TIO = dat & 0x01;  //从一字节最低位开始写
		TSCLK = 1;		   //拉高时钟总线，DS1302把数据读走
		dat >>= 1;		   //数据右移一位 
	}	
}

uchar DS1302_R_Byte()
{
	uchar i, dat;
	for(i = 0; i < 8; i++)  //每次写1bit，写8次
	{
		TSCLK = 0;			//拉低时钟总线，DS1302把数据放到数据总线上
		dat >>= 1; 			//数据右移一位，数据从最低位开始读 
		if(TIO)	dat |= 0x80;//读取数据
		TSCLK = 1;			//拉高时钟总线
	}
	return dat;				//返回读取的数据
}

void DS1302_W_DAT(uchar cmd, uchar dat)
{
	TRST = 0;			 //拉低使能端
	TSCLK = 0;			 //拉低数据总线
	TRST = 1;			 //拉高使能端，开始写数据
	DS1302_W_Byte(cmd);	 //写命令
	DS1302_W_Byte(dat);	 //写数据
}

uchar DS1302_R_DAT(uchar cmd)
{
	uchar dat;
	TRST = 0;			 	//拉低使能端
	TSCLK = 0;				//拉低数据总线
	TRST = 1;				//拉高使能端，开始写数据
	DS1302_W_Byte(cmd);		//写命令
	dat = DS1302_R_Byte();	//读出数据
	return dat;				//返回读出数据
}

void DS1302_Clear_WP()
{
	DS1302_W_DAT(0x8e,0x00);  //把控制寄存器WP位置0
}

void DS1302_Set_WP()
{	
	DS1302_W_DAT(0x8e,0x80); //把控制寄存器WP位置1
	TRST = 0;				 //拉低使能端
	TSCLK = 0;				 //拉低数据总线
} 

void Set_DS1302_Time(uchar addr)
{
	uchar i, j;
	DS1302_Clear_WP();		//清除写保护
	for(i = 0; i < 7; i++)	//写入7个字节的时钟初始值
	{
		j = TimeData[i]/10;	 //BCD码转换
		TimeData[i] %= 10;	 //BCD码转换
		TimeData[i] += j*16; //BCD码转换
		DS1302_W_DAT(addr, TimeData[i]); //先写DS1302时钟日历起始地址，再写数据
		addr += 2;	 //时钟日历寄存器地址+2转向下一个寄存器
	}
	DS1302_Set_WP(); //开起写保护		
}

void Read_DS1302_Time(uchar addr)
{
	uchar i;
	DS1302_Clear_WP();    	//清楚写保护
	for(i = 0; i < 7; i++)	//从DS1302读取7个字节的时钟日历数据
	{
		TimeData[i] = DS1302_R_DAT(addr);//先写入要读取数据的寄存器起始地址，再读出数据存入TimeData数组
		addr += 2;						 //时钟日历寄存器地址+2转向下一个寄存器
	}
	DS1302_Set_WP();   //开起写保护
} 


uchar Dat_Chg_BCD(uchar dat)//数据转BCD
{
    uchar dat1,dat2;
    dat1=dat/10;
    dat2=dat%10;
    dat2=dat2+dat1*16;
    return dat2;
}

uchar BCD_Chg_Dat(uchar dat)//BCD转数据
{
    uchar dat1,dat2;
    dat1=dat/16;
    dat2=dat%16;
    dat2=dat2+dat1*10;
    return dat2;
}