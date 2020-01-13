//���ں���Ͷ�����������̶����õ�P3������P3.2�������Ե�������ʹ�ú��⣬Ȼ������󣬵�һ������������ں���һ��

#include "Sys.h"
int temp=0;//���յ����¶�ֵ���������������ж�
extern uchar password_original[5];//ԭ����
extern uchar IRcord[4]; //���������4���ֽ����ݣ��û��룬�û��룬�����룬���ݷ���
extern uchar IRdata[33];//������ʼ�����ڵ�33λ����
extern uchar Lock;
extern uchar chance;
extern uint Beeptime;
uchar choosemode=0;
extern bit IRpro_ok;    //�����4���ֽ����ݽ�����ɱ�־λ
extern bit IRok;//33λ���ݽ�����ɱ�־λ
extern uchar TimeData[7];
uchar readflag=0;//�Ƿ��ȡ�¶Ⱥ�ʱ��
extern uchar AD_Value;	//�洢ADת���ص�������
extern unsigned char pwm_motor_val;//���ҵ��ռ�ձ�ֵ,ԽС��
extern unsigned char pwm_t;//����
extern unsigned char datas[5];//�¶�ֵ
uchar LightControl=Machine;
//����Human����Ϊ���ƣ�LightHuman��Ч��LightMachineʧЧ������Machine�����ܿ��ƣ�LightMachineʧЧ��LightMachine��Ч
uchar LightHuman=LightOff;
uchar LightMachine=LightOff;

uchar FanControl=Machine;
//����Human����Ϊ���ƣ�LightHuman��Ч��LightMachineʧЧ������Machine�����ܿ��ƣ�LightMachineʧЧ��LightMachine��Ч
uchar FanHuman=FanOff;
uchar FanMachine=FanOff;

void choose(uchar i);
//void openstring();
void Timer1Init();
sbit LED1= P1^0;   //��ȡAD��ֵ�Ƿ�ɹ������ɹ�����ʧ�ܣ�
sbit LED2= P1^1;   //DAC�ɹ���������ɹ�����ʧ�ܣ�
void main()
{
	
	uchar i=0;
	Timer1Init();
	InitLcd1602();
	I2C_init();
//	while(1)//���Թ��������DA���
//	{
//		
//		if (ADC_Read(0x00))	LED1 = 0;	else	LED1 = 1;	
//		AD_Value=LightOff;
//		if (DAC_OUT(AD_Value))	LED2 = 0;	else	LED2 = 1;
//		DisplayOneChar(0,0,AD_Value);
//		Delayms(5);
//	}

//	for(i=1;i<6;i++)//����д��һ�ε����뵽EEPROM
//	{
//		I2C_TransmitData(i,password_original[i-1]);
//		Delayms(5);
//	}
	
	Delayms(5);
	for(i=1;i<6;i++)
	{
		password_original[i-1]=I2C_ReceiveData(i);//��EEPROM��ȡ���룬һ��һλ��һ��5��
		Delayms(5);
	}
	init();//�����߶�ʱ��0���ⲿ�ж�0��ʼ��
	DUAN=0;
	WEI=0;

	Set_DS1302_Time(DS1302_W_ADDR);	//��д��ʱ�������Ĵ�����ʼ��ַ������ʱ��������ֵ
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
		case 0://*******************************************************�ѹ��ţ���������
			Lcd1602_Write_Cmd(0x01);//�����һ������ʾ��ģʽ������
			LcdShowStr(0,0,"Input secret.");
			while(1)
			{
				if(IRok)
				{
					IRcordpro();//������������4���ֽ�����
					IRok=0;//������������ɱ�־λ�ȴ���һ��������
					if(IRpro_ok)//�ж��Ƿ�������
					{
						if(IRcord[2]==0x45)//����
						{
							Lock=LockOff;
							choosemode=1;
						}
						else if(IRcord[2]==0x0c)//����
						{
							LightControl=Human;
							LightHuman=LightOn;
						}
						else if(IRcord[2]==0x18)//�ص�
						{
							LightControl=Human;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x5e)//���ܵ�
						{
							LightControl=Machine;
							LightHuman=LightOff;
						}
						else if(IRcord[2]==0x08)//������
						{
							FanControl=Human;
							FanHuman=FanOn;
						}
						else if(IRcord[2]==0x1c)//�ط���
						{
							FanControl=Human;
							FanHuman=FanOff;
						}
						else if(IRcord[2]==0x5a)//���ܷ���
						{
							FanControl=Machine;
							FanHuman=FanOff;
						}
						IRpro_ok=0;//���������ɱ�־λ
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
						Beep=0;//����������
					}
					if(Beep==0)
					{
						Beeptime++;
						if(Beeptime>100)
							Beep=1;//������ֹͣ
					}
				}
				if(Lock==LockOff)
				{
					InitLcd1602();
					break;
				}
			}		
			break;
		case 1://**********************************************************�ѿ��ţ���ʾ�¶�ʱ��
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
					IRcordpro();//������������4���ֽ�����
					IRok=0;//������������ɱ�־λ�ȴ���һ��������
					if(IRpro_ok)//�ж��Ƿ�������
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
						else if(IRcord[2]==0x08)//������
						{
							FanControl=Human;
							FanHuman=FanOn;
						}
						else if(IRcord[2]==0x1c)//�ط���
						{
							FanControl=Human;
							FanHuman=FanOff;
						}
						else if(IRcord[2]==0x5a)//���ܵ�
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
						IRpro_ok=0;//���������ɱ�־λ
					}
				}
				if(readflag==1)//�ﵽ1����ж�ȡ�¶ȡ����ں�ʱ��
				{
					readflag=0;
					//�¶���ʾ
					temp=getTmpValue();
					displayTemp(temp);
					sendChangeCmd();//�¶�ת��������һ����
//					DisplayOneChar(13,1,'*');
					
					//ʱ����ʾ
					Read_DS1302_Time(DS1302_R_ADDR); //��д��ʱ�������Ĵ�����ʼ��ַ�ٶ���ʱ������д�뵽TimeData������
					DisplayOneStr (8,0,TimeData[6]); //��
					DisplayOneChar (10,0,'-');		 //-
					DisplayOneStr (11,0,TimeData[4]); //��
					DisplayOneChar (13,0,'-');		 //-
					DisplayOneStr (14,0,TimeData[3]);//��
					
					DisplayOneStr (0,1,TimeData[2]); //ʱ
					DisplayOneChar (2,1,':');		 //��
					DisplayOneStr (3,1,TimeData[1]); //��
					DisplayOneChar (5,1,':');		 //��
					DisplayOneStr (6,1,TimeData[0]);//��
					
//					DisplayOneChar(10,1,'o');
				}
				if(Input==0)//����
				{
					LightControl=Human;
					LightHuman=LightOn;
				}
				else if(Input==1)//�ص�
				{
					LightControl=Human;
					LightHuman=LightOff;
				}
				else if(Input==2)//���ܵ�
				{
					LightControl=Machine;
					LightHuman=LightOff;
				}
				else if(Input==4)//������
				{
					FanControl=Human;
					FanHuman=FanOn;
				}
				else if(Input==5)//�ط���
				{
					FanControl=Human;
					FanHuman=FanOff;
				}
				else if(Input==6)//���ܷ���
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
				if(Input==18)//�޸�����
				{
					choosemode=2;
					Lcd1602_Write_Cmd(0x01);
//					ET1=0;
//					TR1=0;
					break;
				}
				
				else if(Input==19)//�������ţ�
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
		case 2://**************************************************************�޸�����
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
	Delayms(1000); //�¶�ת��ʱ����Ҫ750ms����
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
		//��ȡ�����жϷ������л���Ŷ�ʱ����ʱ
		//�¶���ʾ
		displayTemp(getTmpValue());
		sendChangeCmd();
		DisplayOneChar(13,1,'*');
		
		//ʱ����ʾ
		Read_DS1302_Time(DS1302_R_ADDR); //��д��ʱ�������Ĵ�����ʼ��ַ�ٶ���ʱ������д�뵽TimeData������
		DisplayOneStr (8,0,TimeData[6]); //��
		DisplayOneChar (10,0,'-');		 //-
		DisplayOneStr (11,0,TimeData[4]); //��
		DisplayOneChar (13,0,'-');		 //-
		DisplayOneStr (14,0,TimeData[3]);//��
		
		DisplayOneStr (0,1,TimeData[2]); //ʱ
		DisplayOneChar (2,1,':');		 //��
		DisplayOneStr (3,1,TimeData[1]); //��
		DisplayOneChar (5,1,':');		 //��
		DisplayOneStr (6,1,TimeData[0]);//��
		
		DisplayOneChar(10,1,'o');
		*/
	}
//	ET1=1;TR1=1;
	
	pwm_t++;//���ȿ���
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