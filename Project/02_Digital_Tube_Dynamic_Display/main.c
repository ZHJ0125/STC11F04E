/**********************实验测试程序************************
*  平台：Keil U5 + STC11F04E
*  名称：数码管动态显示实验
*  日期：2019-9-30
*  姓名：ZhangHJ
*  说明：数码管静态显示
***********************************************************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define DELAY_TIME 10
#define ON 0
#define OFF 1

sbit DAT=P3^0;			// 74HC164 数据输入
sbit CLK=P3^1;			// 74HC164 时钟输入
//sbit DP=P3^7;			// 小数点
//sbit DP1=P3^5;
sbit DPY0 = P1^0;		// 独立位选
sbit DPY1 = P1^1;
sbit DPY2 = P1^2;
sbit DPY3 = P1^3;
sbit KEY = P3^2;		// INT0 按键,按下为低电平

// 数码管段选数组	数字0~9和全灭
uchar code tab[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xff};
// 数码管位选数组	全灭和独立3~0
uchar code wei[]={0xf0,0xf8,0xf4,0xf2,0xf1};



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



/**********************************************************
*  函数名称：按位控制数码管动态显示函数
*  日期：2019-9-30
*  姓名：ZhangHJ
*  说明：实现4个数码管显示 4321 的效果
* 			 数码管引脚高电平有效,首先设置各位段选信号,然后给寄存器发送数据
*				 延时一段时间实现数字显示,最后清除段选信号清屏.
***********************************************************/
void test_light_bit()
{
		DPY0 = ON;
		DPY1 = OFF;
		DPY2 = OFF;
		DPY3 = OFF;
		SendByte_74HC164(1);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
	
		DPY0 = OFF;
		DPY1 = ON;
		DPY2 = OFF;
		DPY3 = OFF;
		SendByte_74HC164(2);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
	
		DPY0 = OFF;
		DPY1 = OFF;
		DPY2 = ON;
		DPY3 = OFF;
		SendByte_74HC164(3);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
		
		DPY0 = OFF;
		DPY1 = OFF;
		DPY2 = OFF;
		DPY3 = ON;
		SendByte_74HC164(4);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
}



/**********************************************************
*  函数名称：按字节控制数码管动态显示函数
*  日期：2019-9-30
*  姓名：ZhangHJ
*  说明：实现4个数码管显示 1234 的效果
* 			 数码管引脚低电平有效,首先关闭位选信号,然后给寄存器发送数据(开启段选),
*				 开启位选控制并延时一段时间以显示数字,最后关闭位选信号清屏.
***********************************************************/
void test_light_byte()
{
		P1 |= 0x0f;							// 关掉位选
		SendByte_74HC164(1);		// 开启段选
		P1 &= 0xf7;							// 开启位选
		delay_ms(DELAY_TIME);		// 延时显示
		P1 |= 0x0f;							// 关掉位选
		
		SendByte_74HC164(2);
		P1 &= 0xfB;
		delay_ms(DELAY_TIME);
		P1 |= 0x0f;
		
		SendByte_74HC164(3);
		P1 &= 0xfD;
		delay_ms(DELAY_TIME);
		P1 |= 0x0f;

		SendByte_74HC164(4);
		P1 &= 0xfe;
		delay_ms(DELAY_TIME);
}



//主函数功能：正常状态显示1234,按键INT0按下时显示4321
void main()
{
	while(1)
	{
		if(KEY == 0)
		{
			delay_ms(20);
			while(KEY == 0)				// INT0按键被按下
			{
				test_light_bit();		// 显示4321
			}
		}
		test_light_byte();			// 显示1234
	}
}









