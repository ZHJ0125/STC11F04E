#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)		// 1ms

sbit DAT = P3^0;				// 74HC164 数据输入端口
sbit CLK = P3^1;				// 74HC164 时钟输入端口
sbit KEY = P3^2;				// 按键端口
uint num = 0;					// 显示的数字
uint count;

// 定义数码管段选(不加小数点0~9)
uchar code table1[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82};

/**********************************************************
*  函数名称：低精度延时函数
*  日期：2019-9-7
*  姓名：ZhangHJ
*  说明：嵌套循环延时
***********************************************************/
void delay(unsigned int mstime)
{
	int i,j;
	for(i=mstime; i>=0; i--)
		for(j=114; j>=0; j--);
}


/**********************************************************
*  函数名称：精确延时50ms函数
*  日期：2019-10-25
*  姓名：ZhangHJ
*  说明：由STC-ISP自动生成
***********************************************************/
//void Delay50ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 3;
//	j = 26;
//	k = 223;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}





/**********************************************************
*  函数名称：74HC164发送Byte数据函数
*  日期：2019-9-29
*  姓名：ZhangHJ
*  说明：74HC164移位寄存器输入一字节数据发给寄存器
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=table1[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;				// 制造一个上升沿
		CLK=1;
		num>>=1;			// 将数据发送到寄存器
	}
}



/**********************************************************
*  函数名称：配置定时器T0方式1
*  日期：2019-11-1
*  姓名：ZhangHJ
*  说明：
***********************************************************/
void configTimeInt0()
{
	TMOD = 0x01;		// 定时器0模式1
	TL0 = T1MS;			// 装入初始数据
	TH0 = T1MS >> 8;
//	TH0 = 0;
	// 配置控制寄存器TCON
	TR0 = 1;			// 允许T0计数
	ET0 = 1;			// 开启T0中断
	EA = 1;				// 开启总中断
	count = 0;
}


/**********************************************************
*  函数名称：定时器T0方式1服务函数
*  日期：2019-11-1
*  姓名：ZhangHJ
*  说明：中断服务函数功能为
***********************************************************/
void tm0_isr() interrupt 1
{
//	EA = 0;						// 关闭总中断
	TL0 = T1MS;
	TH0 = T1MS >> 8;
//	TH0 = 0;
	if(count-- == 0)
	{
		count = 1000;
		num ++;
		num = num % 10;
	}
//	EA = 1;						// 开启总中断
}


int main()
{
	configTimeInt0();			// 配置定时器 T0
	P1 &= 0xf0;					// 位选全部选中
	while(1)
	{
		SendByte_74HC164(num);
		delay(600);
	}
}
