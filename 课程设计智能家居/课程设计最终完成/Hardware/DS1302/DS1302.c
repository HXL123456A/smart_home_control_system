#include "Sys.h"

//ʱ�������ݴ����飬�롢�֡�ʱ���ա��¡��ܡ��� ��ֵΪ= 16��2��15�� ��1 23:58:50
uchar TimeData[7]={50, 58, 21, 15, 2, 1, 16};

void DS1302_W_Byte(uchar dat)
{
	uchar i;
	for(i = 0; i < 8; i++) //ÿ��д1bit��д8��
	{
		TSCLK = 0;		   //����ʱ������
		TIO = dat & 0x01;  //��һ�ֽ����λ��ʼд
		TSCLK = 1;		   //����ʱ�����ߣ�DS1302�����ݶ���
		dat >>= 1;		   //��������һλ 
	}	
}

uchar DS1302_R_Byte()
{
	uchar i, dat;
	for(i = 0; i < 8; i++)  //ÿ��д1bit��д8��
	{
		TSCLK = 0;			//����ʱ�����ߣ�DS1302�����ݷŵ�����������
		dat >>= 1; 			//��������һλ�����ݴ����λ��ʼ�� 
		if(TIO)	dat |= 0x80;//��ȡ����
		TSCLK = 1;			//����ʱ������
	}
	return dat;				//���ض�ȡ������
}

void DS1302_W_DAT(uchar cmd, uchar dat)
{
	TRST = 0;			 //����ʹ�ܶ�
	TSCLK = 0;			 //������������
	TRST = 1;			 //����ʹ�ܶˣ���ʼд����
	DS1302_W_Byte(cmd);	 //д����
	DS1302_W_Byte(dat);	 //д����
}

uchar DS1302_R_DAT(uchar cmd)
{
	uchar dat;
	TRST = 0;			 	//����ʹ�ܶ�
	TSCLK = 0;				//������������
	TRST = 1;				//����ʹ�ܶˣ���ʼд����
	DS1302_W_Byte(cmd);		//д����
	dat = DS1302_R_Byte();	//��������
	return dat;				//���ض�������
}

void DS1302_Clear_WP()
{
	DS1302_W_DAT(0x8e,0x00);  //�ѿ��ƼĴ���WPλ��0
}

void DS1302_Set_WP()
{	
	DS1302_W_DAT(0x8e,0x80); //�ѿ��ƼĴ���WPλ��1
	TRST = 0;				 //����ʹ�ܶ�
	TSCLK = 0;				 //������������
} 

void Set_DS1302_Time(uchar addr)
{
	uchar i, j;
	DS1302_Clear_WP();		//���д����
	for(i = 0; i < 7; i++)	//д��7���ֽڵ�ʱ�ӳ�ʼֵ
	{
		j = TimeData[i]/10;	 //BCD��ת��
		TimeData[i] %= 10;	 //BCD��ת��
		TimeData[i] += j*16; //BCD��ת��
		DS1302_W_DAT(addr, TimeData[i]); //��дDS1302ʱ��������ʼ��ַ����д����
		addr += 2;	 //ʱ�������Ĵ�����ַ+2ת����һ���Ĵ���
	}
	DS1302_Set_WP(); //����д����		
}

void Read_DS1302_Time(uchar addr)
{
	uchar i;
	DS1302_Clear_WP();    	//���д����
	for(i = 0; i < 7; i++)	//��DS1302��ȡ7���ֽڵ�ʱ����������
	{
		TimeData[i] = DS1302_R_DAT(addr);//��д��Ҫ��ȡ���ݵļĴ�����ʼ��ַ���ٶ������ݴ���TimeData����
		addr += 2;						 //ʱ�������Ĵ�����ַ+2ת����һ���Ĵ���
	}
	DS1302_Set_WP();   //����д����
} 


uchar Dat_Chg_BCD(uchar dat)//����תBCD
{
    uchar dat1,dat2;
    dat1=dat/10;
    dat2=dat%10;
    dat2=dat2+dat1*16;
    return dat2;
}

uchar BCD_Chg_Dat(uchar dat)//BCDת����
{
    uchar dat1,dat2;
    dat1=dat/16;
    dat2=dat%16;
    dat2=dat2+dat1*10;
    return dat2;
}