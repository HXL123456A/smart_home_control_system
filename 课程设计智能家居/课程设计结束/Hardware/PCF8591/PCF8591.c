#include "Sys.h"

uchar AD_Value;	//�洢ADת���ص�������

/*DAC���*/
bit DAC_OUT(uchar DAT)
{
	I2C_Start();
	I2C_send_byte(PCF8591_ADDR+0);
	if (!Test_ACK())
	{
		return(0);
	}
	I2C_send_byte(DACOUT_EN);	//DA���ʹ�� 
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

/*��AD����*/
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