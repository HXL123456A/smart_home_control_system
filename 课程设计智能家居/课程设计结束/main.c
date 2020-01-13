//由于红外和独立、矩阵键盘都是用的P3（红外P3.2），所以当开锁后使用红外，然后关锁后，第一次输入密码会在后面一点

#include "Sys.h"
int temp=0;//接收到的温度值，有正负，用于判断
extern uchar password_original[5];//原密码
extern uchar IRcord[4]; //储存解码后的4个字节数据，用户码，用户码，数据码，数据反码
extern uchar IRdata[33];//包含起始码在内的33位数据
extern uchar Lock;
extern uchar chance;
extern uint Beeptime;
uchar choosemode=0;
extern bit IRpro_ok;    //解码后4个字节数据接收完成标志位
extern bit IRok;//33位数据接收完成标志位
extern uchar TimeData[7];
uchar readflag=0;//是否读取温度和时间
extern uchar AD_Value;	//存储AD转换回的数字量
extern unsigned char pwm_motor_val;//左右电机占空比值,越小快
extern unsigned char pwm_t;//周期
extern unsigned char datas[5];//温度值
uchar LightControl=Machine;
//等于Human：人为控制，LightHuman有效，LightMachine失效，等于Machine：智能控制，LightMachine失效，LightMachine有效
uchar LightHuman=LightOff;
uchar LightMachine=LightOff;

uchar FanControl=Machine;
//等于Human：人为控制，LightHuman有效，LightMachine失效，等于Machine：智能控制，LightMachine失效，LightMachine有效
uchar FanHuman=FanOff;
uchar FanMachine=FanOff;

void choose(uchar i);
//void openstring();
void Timer1Init();
sbit LED1= P1^0;   //读取AD的值是否成功（亮成功，灭失败）
sbit LED2= P1^1;   //DAC成功输出（亮成功，灭失败）
void main()
{
	
	uchar i=0;
	Timer1Init();
	InitLcd1602();
	I2C_init();
//	while(1)//测试光敏电阻和DA输出
//	{
//		
//		if (ADC_Read(0x00))	LED1 = 0;	else	LED1 = 1;	
//		AD_Value=LightOff;
//		if (DAC_OUT(AD_Value))	LED2 = 0;	else	LED2 = 1;
//		DisplayOneChar(0,0,AD_Value);
//		Delayms(5);
//	}

//	for(i=1;i<6;i++)//用于写第一次的密码到EEPROM
//	{
//		I2C_TransmitData(i,password_original[i-1]);
//		Delayms(5);
//	}
	
	Delayms(5);
	for(i=1;i<6;i++)
	{
		password_original[i-1]=I2C_ReceiveData(i);//从EEPROM读取密码，一次一位，一共5次
		Delayms(5);
	}
	init();//红外线定时器0和外部中断0初始化
	DUAN=0;
	WEI=0;

	Set_DS1302_Time(DS1302_W_ADDR);	//先写入时钟日历寄存器起始地址再设置时钟日历初值
	while(1)
	{
		choose(choosemode);
	}
}

void choose(uchar i)
{
	
	uchar Input=22;
	switch(i)
	{
		case 0://*******************************************************已关门，输入密码
			Lcd1602_Write_Cmd(0x01);//清除上一次所显示的模式的内容
			LcdShowStr(0,0,"Input secret.");
			while(1)
			{
				if(IRok)
				{
					IRcordpro();//根据脉宽解码出4个字节数据
					IRok=0;//清零脉宽检查完成标志位等待下一次脉宽检查
					if(IRpro_ok)//判断是否解码完成
					{
						if(IRcord[2]==0x45)//开锁
						{
							Lock=LockOff;
							choosemode=1;
						}
						else if(IRcord[2]==0x0c)//开灯
						{
							LightControl=Human;
							LightHuman=LightOn;
						}
						else if(IRcord[2]==0x18)//关灯
						{
							LightControl=Human;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x5e)//智能灯
						{
							LightControl=Machine;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x08)//开风扇
						{
							FanControl=Human;
							FanHuman=FanOn;
						}
						else if(IRcord[2]==0x1c)//关风扇
						{
							FanControl=Human;
							FanHuman=FanOff;
						}
						else if(IRcord[2]==0x5a)//智能风扇
						{
							FanControl=Machine;
							FanHuman=FanOff;
						}
						IRpro_ok=0;//清零解码完成标志位
					}
				}
				if(LightControl==Human)
				{
					AD_Value=LightHuman;
				}
				else if(LightControl==Machine)
				{
					AD_Value=LightOff;
				}
				DAC_OUT(AD_Value);
				
				if(chance>0)
				{
					LcdShowStr(0,1,"Input:");
					DisplayOneChar(15,0,chance+'0');
					KeyAction();
				}
				else
				{
					LcdShowStr(0,0,"Only Inred open!");
					LcdShowStr(0,1,"      ");
					
					
					if(Beeptime==0)
					{
						Beep=0;//蜂鸣器报警
					}
					if(Beep==0)
					{
						Beeptime++;
						if(Beeptime>100)
							Beep=1;//蜂鸣器停止
					}
				}
				if(Lock==LockOff)
				{
					InitLcd1602();
					break;
				}
			}		
			break;
		case 1://**********************************************************已开门，显示温度时间
//			Timer1Init();
//		ET1=1;
//		TR1=1;
			while(1)
			{
				
				Input=22;
//				openstring();
				Input=KeyScan();
				if(IRok)
				{
					IRcordpro();//根据脉宽解码出4个字节数据
					IRok=0;//清零脉宽检查完成标志位等待下一次脉宽检查
					if(IRpro_ok)//判断是否解码完成
					{
						if(IRcord[2]==0x0c)
						{
							LightControl=Human;
							LightHuman=LightOn;
						}
						else if(IRcord[2]==0x18)
						{
							LightControl=Human;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x5e)
						{
							LightControl=Machine;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x08)//开风扇
						{
							FanControl=Human;
							FanHuman=FanOn;
						}
						else if(IRcord[2]==0x1c)//关风扇
						{
							FanControl=Human;
							FanHuman=FanOff;
						}
						else if(IRcord[2]==0x5a)//智能灯
						{
							FanControl=Machine;
							FanHuman=FanOff;
						}
						else if(IRcord[2]==0x47)
						{
							choosemode=0;
							chance=3;
							Lock=LockOn;
							ET1=0;TR1=0;
							LightControl=Machine;
							AD_Value=LightOff;
							break;
						}
						IRpro_ok=0;//清零解码完成标志位
					}
				}
				if(readflag==1)//达到1秒进行读取温度、日期和时间
				{
					readflag=0;
					//温度显示
					temp=getTmpValue();
					displayTemp(temp);
					sendChangeCmd();//温度转换，给下一次用
//					DisplayOneChar(13,1,'*');
					
					//时间显示
					Read_DS1302_Time(DS1302_R_ADDR); //先写入时钟日历寄存器起始地址再读出时钟日历写入到TimeData数组中
					DisplayOneStr (8,0,TimeData[6]); //年
					DisplayOneChar (10,0,'-');		 //-
					DisplayOneStr (11,0,TimeData[4]); //月
					DisplayOneChar (13,0,'-');		 //-
					DisplayOneStr (14,0,TimeData[3]);//日
					
					DisplayOneStr (0,1,TimeData[2]); //时
					DisplayOneChar (2,1,':');		 //：
					DisplayOneStr (3,1,TimeData[1]); //分
					DisplayOneChar (5,1,':');		 //：
					DisplayOneStr (6,1,TimeData[0]);//秒
					
//					DisplayOneChar(10,1,'o');
				}
				if(Input==0)//开灯
				{
					LightControl=Human;
					LightHuman=LightOn;
				}
				else if(Input==1)//关灯
				{
					LightControl=Human;
					LightHuman=LightOff;
				}
				else if(Input==2)//智能灯
				{
					LightControl=Machine;
					LightHuman=LightOff;
				}
				else if(Input==4)//开风扇
				{
					FanControl=Human;
					FanHuman=FanOn;
				}
				else if(Input==5)//关风扇
				{
					FanControl=Human;
					FanHuman=FanOff;
				}
				else if(Input==6)//智能风扇
				{
					FanControl=Machine;
					FanHuman=FanOff;
				}
				
				if(LightControl==Human)
				{
					AD_Value=LightHuman;
				}
				else if(LightControl==Machine)
				{
					uchar Hour;
					ADC_Read(0x00);
					Hour=BCD_Chg_Dat(TimeData[2]);
					if(!(Hour>20&&Hour<23))
					{
						AD_Value=LightOff;
					}
				}
				DAC_OUT(AD_Value);
				if(Input==18)//修改密码
				{
					choosemode=2;
					Lcd1602_Write_Cmd(0x01);
//					ET1=0;
//					TR1=0;
					break;
				}
				
				else if(Input==19)//关锁（门）
				{
					choosemode=0;
					chance=3;
					Lock=LockOn;
//					ET1=0;
//					TR1=0;
					LightControl=Machine;
					FanControl=Machine;
					AD_Value=LightOff;
					_4IN=FanOff;
					break;
				}
				if(_4IN==FanOn)
				{
					DisplayOneChar(13,1,'*');
				}
				else if(_4IN==FanOff)
				{
					DisplayOneChar(13,1,' ');
				}
				if(AD_Value!=LightOff)
				{
					DisplayOneChar(10,1,'o');
				}
				else
				{
					DisplayOneChar(10,1,' ');
				}
			}
			break;
		case 2://**************************************************************修改密码
			Lcd1602_Write_Cmd(0x01);
			while(1)
			{
				uchar change=0;
				LcdShowStr(0,0,"Change secret.");
				LcdShowStr(0,1,"New secret:");
				change=changesecret();
				if(change==1)
				{
					
					break;
				}
			}
			break;
	}
}
/*
void openstring()
{
//	LcdShowStr(0,0,"Open");
	Delayms(1000); //温度转换时间需要750ms以上
	displayTemp(getTmpValue());
	sendChangeCmd();
	LcdShowStr(13,0,"Off");
//	sendChangeCmd();
//	Delayms(1000);
//	displayTemp(getTmpValue);
	
}
*/
void Timer1Init()
{
	EA=1;
	ET1=1;
	TMOD|=0x10;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	TR1=1;
}

void Timer1() interrupt 3
{
	static timer1num=0;

	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	timer1num++;
	
//	ET1=0;TR1=0;
	if(timer1num==20)
	{
		timer1num=0;
		readflag=1;
		/*
		//读取放在中断服务函数中会干扰定时器计时
		//温度显示
		displayTemp(getTmpValue());
		sendChangeCmd();
		DisplayOneChar(13,1,'*');
		
		//时间显示
		Read_DS1302_Time(DS1302_R_ADDR); //先写入时钟日历寄存器起始地址再读出时钟日历写入到TimeData数组中
		DisplayOneStr (8,0,TimeData[6]); //年
		DisplayOneChar (10,0,'-');		 //-
		DisplayOneStr (11,0,TimeData[4]); //月
		DisplayOneChar (13,0,'-');		 //-
		DisplayOneStr (14,0,TimeData[3]);//日
		
		DisplayOneStr (0,1,TimeData[2]); //时
		DisplayOneChar (2,1,':');		 //：
		DisplayOneStr (3,1,TimeData[1]); //分
		DisplayOneChar (5,1,':');		 //：
		DisplayOneStr (6,1,TimeData[0]);//秒
		
		DisplayOneChar(10,1,'o');
		*/
	}
//	ET1=1;TR1=1;
	
	pwm_t++;//风扇控制
	if(pwm_t == 255)
		FanMachine = FanOff;
	else if(pwm_t==pwm_motor_val)
		FanMachine = FanOn;	
//	_4IN=FanMachine;
	if(choosemode==0)
	{
		_4IN = FanHuman;
	}
	if(choosemode==1||choosemode==2)
	{
		if(FanControl==Machine)
		{
			if(temp>0&&datas[1]>=3&&datas[2]>=1)
			{
				_4IN=FanMachine;
			}
			else
				_4IN=FanOff;
		}
//		else if(FanControl==Human)
//		{
//			_4IN=FanHuman;
//		}

	}
	
	if(FanControl==Human)
	{
		_4IN=FanHuman;
	}

}