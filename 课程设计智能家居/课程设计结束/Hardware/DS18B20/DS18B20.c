#include "Sys.h"

unsigned char datas[] = {0, 0, 0, 0, 0};

void dsInit()
 {
    
    unsigned int i;  
    ds = 0;
    i = 100;  
     while(i>0) i--;
    ds = 1;   
    i = 4;
     while(i>0) i--;
 }
 
void dsWait()
 {
      unsigned int i;
      while(ds);  
      while(~ds);
      i = 4;
      while(i > 0) i--;
}


bit readBit()
{
    unsigned int i;
    bit b;
    ds = 0;
    i++;   
    ds = 1; 
   i++; i++;  
    b = ds;
    i = 8; 
    while(i>0) i--;
    return b;
}

unsigned char readByte()
{
    unsigned int i;
    unsigned char j, dat;
   dat = 0;
    for(i=0; i<8; i++)
    {
        j = readBit();
      
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}


void writeByte(unsigned char dat)
{
    unsigned int i;
    unsigned char j;
    bit b;
    for(j = 0; j < 8; j++)
    {
        b = dat & 0x01;
        dat >>= 1;
    
        if(b)   
        {
           ds = 0;          i++; i++;  
            ds = 1;    
            i = 8; while(i>0) i--;  
        }
        else  
        {
            ds = 0;
          i = 8; while(i>0) i--;  
            ds = 1;
           i++; i++;
        }
   }
}


void sendChangeCmd()
{
    dsInit();    
    dsWait();   
    Delayms(1);    
    writeByte(0xcc);
    writeByte(0x44);
}

void sendReadCmd()
{
    dsInit();
    dsWait();
    Delayms(1);
    writeByte(0xcc); 
    writeByte(0xbe); 
}


int getTmpValue()
{
    unsigned int tmpvalue;
    int value; 
    float t;
    unsigned char low, high;
    sendReadCmd();
    
    low = readByte(); 
    high = readByte();
   
    tmpvalue = high;
    tmpvalue <<= 8;
    tmpvalue |= low;
    value = tmpvalue;
    
  
    t = value * 0.0625;
    
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //大于0加0.5, 小于0减0.5
    return value;
}

void displayTemp(int v) 
{
    unsigned char count;
//    unsigned char datas[] = {0, 0, 0, 0, 0};
    unsigned int tmp = abs(v);
    datas[0] = tmp / 10000;
    datas[1] = tmp % 10000 / 1000;
    datas[2] = tmp % 1000 / 100;
    datas[3] = tmp % 100 / 10;
    datas[4] = tmp % 10;
    Lcd1602_Write_Cmd(0x80);
    if(v < 0)
    {
        Lcd1602_Write_Data('-');
   }
    else
    {
       Lcd1602_Write_Data('+');
    }
    if(datas[0] != 0)
    {
        Lcd1602_Write_Data('0'+datas[0]);
    }
    for(count = 1; count != 5; count++)
    {
        Lcd1602_Write_Data('0'+datas[count]);
        if(count == 2)
        {
            Lcd1602_Write_Data('.');
        }
    }
		Lcd1602_Write_Data(0xdf);
		Lcd1602_Write_Data('C');
}


