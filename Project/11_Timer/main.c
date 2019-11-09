#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/20)		// 50ms
#define NUMBER_LOOP				// 定义数字循环

sbit DAT = P3^0;				// 74HC164 数据输入端口
sbit CLK = P3^1;				// 74HC164 时钟输入端口
sbit KEY = P3^2;				// 按键端口
uint num = 0;					// 显示的数字
uint count = 20;				// 循环次数
uchar LOOP = 0xFE;				// 设置数码管循环点亮

// 定义数码管段选(不加小数点0~9)
#ifdef NUMBER_LOOP
uchar code table1[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82};
#endif

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
*  函数名称：74HC164发送Byte数据函数
*  日期：2019-11-5
*  姓名：ZhangHJ
*  说明：74HC164移位寄存器输入一字节数据发给寄存器
*		 1. 如果在数字循环模式,则使用数码管段选数组
*		 2. 如果在数码管段循环模式,则直接使用参数byte
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	#ifdef NUMBER_LOOP		// 数字循环模式
		num = table1[byte];
	#else
		num = byte;
	#endif
	
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
*  说明：1. 配置定时器模式 TMOD
*		 2. 定时器装入初值
*		 3. 配置控制寄存器 TCON
*		 4. 开启中断开关
***********************************************************/
void configTimeInt0()
{
	AUXR &= 0x7F;
	TMOD = 0x01;		// 定时器0模式1
	TL0 = T1MS;			// 装入初始数据
	TH0 = T1MS >> 8;
	TR0 = 1;			// T0开始计数
	ET0 = 1;			// 开启T0中断
	EA = 1;				// 开启总中断
}


/**********************************************************
*  函数名称：定时器T0方式1服务函数
*  日期：2019-11-5
*  姓名：ZhangHJ
*  说明：中断服务函数功能为：定时1S,在数码管上循环显示0~9或循环点亮每一段
*		 1. 如果在数字循环模式,则在数码管上循环显示0~9
*		 2. 如果在数码管段循环模式,则循环点亮每一段
***********************************************************/
void tm0_isr() interrupt 1
{
//	EA = 0;						// 关闭总中断
	TL0 = T1MS;
	TH0 = T1MS >> 8;

	if(count-- == 0)
	{
		count = 20;
		#ifdef NUMBER_LOOP		// 循环显示 0~9
			num ++;
			num = num % 10;
		#else					// 循环点亮数码管
			num = LOOP;
			LOOP = _crol_(LOOP, 1);
		#endif
	}
//	EA = 1;						// 开启总中断
}



// 主函数功能为：定时1S,在数码管上循环显示0~9或循环点亮每一段
int main()
{
	configTimeInt0();			// 配置定时器 T0
	P1 &= 0xf0;					// 位选全部选中
	while(1)
	{
		SendByte_74HC164(num);
		delay(60);
	}
}