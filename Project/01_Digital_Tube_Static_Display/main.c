/**********************实验测试程序************************
*  平台：Keil U5 + STC11F04E
*  名称：数码管实验
*  日期：2019-9-29
*  姓名：ZhangHJ
*  说明：数码管静态显示
***********************************************************/
#include "reg52.h"
#define uint unsigned int
#define uchar unsigned char

sbit DAT=P3^0;
sbit CLK=P3^1;
sbit DP=P3^7;

// 数码管段选数组
uchar code tab[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82};

/**********************************************************
*  函数名称：低精度延时函数
*  日期：2019-9-7
*  姓名：ZhangHJ
*  说明：嵌套循环延时
***********************************************************/
void delay_ms(unsigned int mstime)
{
	int i,j;
	for(i=mstime; i>=0; i--)
		for(j=112; j>=0; j--);
}


/**********************************************************
*  函数名称：74HC164发送Byte函数
*  日期：2019-9-29
*  姓名：ZhangHJ
*  说明：74HC164移位寄存器输入一字节数据发给寄存器
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=tab[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;					// 制造一个上升沿
		CLK=1;
		num>>=1;				// 将数据发送到寄存器
	}
}


  
void main()
{
	int num;
	P1 &= 0Xf0;				// 位选
	//DP = 0;					// 小数点
	while(1)
	{
		for(num=0; num<10; num++)
		{
			delay_ms(50);
			SendByte_74HC164(num);
			delay_ms(2000);
		}
	}
}









