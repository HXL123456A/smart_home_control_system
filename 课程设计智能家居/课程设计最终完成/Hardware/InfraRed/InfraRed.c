#include "Sys.h"


uchar IRtime;    //储存检测红外高低电平持续时间
uchar IRcord[4]; //储存解码后的4个字节数据
uchar IRdata[33];//包含起始码在内的33位数据
bit IRpro_ok;    //解码后4个字节数据接收完成标志位
bit IRok;        //33位数据接收完成标志位


void init()
{
    TMOD|=0x02;//设置定时器0工作模式2，8位自动重装
    TL0=TH0=0;//初始化定时器0寄存器，定时器0溢出一次时间为256个机器周期
    EA=1;
    ET0=1;
    TR0=1;
    
    IT0=1;//设置外部中断0跳边沿触发方式
    EX0=1;
    

}


//定时器中断，每中断一次需要256*1.085us=277.76us（256个机器周期，晶振频率位11.0592Mhz，机器周期=12*晶振周期）
void time0() interrupt 1
{
    IRtime++;//277.76us
}

//外部中断0存入33次脉宽
void int0() interrupt 0
{
    static uchar i;//静态变量用于存入33次数据计数
    static bit startflag;//开始储存脉宽标志位
    if(startflag)//标志被置1则开始存储33次脉冲宽度，一位一位存
    {
        if((IRtime<53)&&(IRtime>=32))i=0;//判断引导码，如果是引导码则从起始码开始存
        IRdata[i]=IRtime;//以T0溢出的次数来计算脉宽把这个时间存放在数组
        IRtime=0;//计数清零
        i++;//计数脉宽存入次数自加
        if(i==33)//i=33就表示已经存入了33次脉宽
        {
            IRok=1;//脉宽检查完成
            i=0;//把脉宽计数清零准备下次存入
        }
    }
    else
    {
        IRtime=0;//定时器0计数清零，因为初始化时就启动了，即使没有收到红外数据也再加
        startflag=1;//开始处理标志位置1
    }
}

//把提取的33次脉宽解码 NEC协议
void IRcordpro()
{
    uchar i;//计数处理4个字节
    uchar j;//用于处理1个字节的8位数据
    uchar k;//用于计数处理33次脉宽
    k=1;//从第一位脉宽开始处理，丢掉起始码
    for(i=0;i<4;i++)
    {
        for(j=0;j<8;j++)
        {
            if(IRdata[k]>5)    IRcord[i]|=0x80;//如果脉宽大于数据0标准的1125us那么就判断为数据1
            
            if(j<7)    IRcord[i]>>=1;//只能移动7次，防止最后一位移出
            k++;//处理下一次脉宽
        }
    }
    IRpro_ok=1;//解码完成
}