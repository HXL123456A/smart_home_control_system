#include "Sys.h"

uchar AD_Value;	//存储AD转换回的数字量

/*DAC输出*/
bit DAC_OUT(uchar DAT)
{
	I2C_Start();
	I2C_send_byte(PCF8591_ADDR+0);
	if (!Test_ACK())
	{
		return(0);
	}
	I2C_send_byte(DACOUT_EN);	//DA输出使能 
	if (!Test_ACK())
	{
		return(0);
	}
	I2C_send_byte(DAT);
	if (!Test_ACK())
	{
		return(0);
	}
	I2C_Stop();
	return(1);	
}

/*读AD数据*/
bit ADC_Read(uchar CON)
{
	I2C_Start();
	I2C_send_byte(PCF8591_ADDR+0);
	if (!Test_ACK())
	{
		return(0);
	}
	I2C_send_byte(CON);
	Master_ACK(0);
	I2C_Start();
	I2C_send_byte(PCF8591_ADDR+1);
	if (!Test_ACK())
	{
		return(0);
	}
	AD_Value = I2C_read_byte();
	Master_ACK(0);
	I2C_Stop();
	return(1);	
}