#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define Hex2Char(x) ((x/10)*10+(x%10)-48)
sbit DAT=P3^0;			// 74HC164 数据输入
sbit CLK=P3^1;			// 74HC164 时钟输入
uchar show_data;			// 接收数据
uchar code tab[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xff};		// 数码管段选数组	数字0~9和全灭

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
		CLK=0;				// 制造一个上升沿
		CLK=1;
		num>>=1;			// 将数据发送到寄存器
	}
}



/**********************************************************
*  函数名称：配置串口1
*  日期：2019-11-21
*  姓名：ZhangHJ
*  说明：1. 设置定时器12分频
*		 2. 配置定时器T1方式2(8位自动重装)
*		 3. 定时器装初值,设置波特率
*		 4. 设置波特率倍增位,波特率不加倍
*		 5. 设置串行口控制寄存器,8位数据,允许串行接收
*		 6. 开启总中断和串口中断
*		 7. 定时器T1运行
***********************************************************/
void UartConfig()
{
	AUXR &= 0xBF;	// 定时器T1分频12T
	TMOD = 0x20;	// 定时器1方式2(8位自动重装)
	TH1 = 0xFD;		// 定时器重装值
	TL1 = 0xFD;		// 定时器初值
	PCON = 0x00;	// 波特率不加倍	0x80加倍(SMOD=1)
	SCON = 0x50;	// 波特率控制寄存器,8位UART,REN=1
	EA = 1;			// 打开总中断
	ES = 1;			// 打开串行口中断
	TR1 = 1;		// 定时器T1运行
}



/**********************************************************
*  函数名称：串口1中断服务函数
*  日期：2019-11-21
*  姓名：ZhangHJ
*  说明：1. 接收数据
*		 2. 清除接收标志位
*		 3. 发送接收到的数据
*		 4. 等待发送完成
*		 5. 清除发送标志位
***********************************************************/
void UartService() interrupt 4
{
	uchar temp;
	temp = SBUF;	// 接收数据
	RI = 0;			// 清除接收中断标志位
	show_data = temp;
//	SBUF = show_data;
//	while(!TI);		// 等待发送完成
//	TI = 0;			// 清除发送中断标志位
}


// 这是从机的功能函数，晶振11.0592MHz
// 主函数功能：接收由主机发来的数据，并将其显示在数码管上
// 注意：STC-ISP软件烧录时需要选择使用外部晶振
void main()
{
	UartConfig();	// 配置串口
	P1 &= 0xf0;
	while(1)
	{
		SendByte_74HC164(Hex2Char(show_data));
		delay_ms(20);
	}
}