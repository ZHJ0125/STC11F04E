#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define Hex2Char(x) ((x/10)*10+(x%10)-48)
sbit DAT=P3^0;			// 74HC164 数据输入
sbit CLK=P3^1;			// 74HC164 时钟输入
sbit KEY = P3^2;		// 按键端口
uchar show_data;		// 接收数据
uchar number = 0;	// 数字0~9

/**********************************************************
*  函数名称：精确延时50ms函数 @11.0592MHz
*  日期：2019-10-25
*  姓名：ZhangHJ
*  说明：由STC-ISP自动生成
***********************************************************/
void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
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
*  函数名称：配置外部中断0
*  日期：2019-10-22
*  姓名：ZhangHJ
*  说明：1. 选择为下降沿触发方式(为1代表下降沿触发，为0代表低电平触发)
*		 2. 使能外部中断0
* 		 3. 使能总中断
***********************************************************/
void configExtInt0()
{
	IT0 = 1;	//选择为下降沿触发方式(为1代表下降沿触发，为0代表低电平触发)
	EX0 = 1;	//使能外部中断0
	EA = 1;  	//使能总中断
}



/**********************************************************
*  函数名称：外部中断0服务函数
*  日期：2019-11-21
*  姓名：ZhangHJ
*  说明：1. 中断服务函数功能为,使num在0~9之间循环变化
*		 2. 发送number的十六进制数值
***********************************************************/
void extInt0() interrupt 0
{
	EA = 0;							// 关闭总中断
	Delay50ms();					// 延时防抖
	if(KEY == 0)
	{
		number ++;
		number = number % 10;
		SBUF = number+48;
		while(!TI);					// 等待发送完毕
		TI=0;						// 清除发送标志位
	}
	EA = 1;							// 开启总中断
}


// 这是主机的功能函数，晶振11.0592MHz
// 主函数功能：通过按键外部中断控制number在0~9之间循环，并将number的十六进制数据发送至从机
// 注意：STC-ISP需要选择使用外部时钟
void main()
{
	configExtInt0();
	UartConfig();					// 配置串口
	while(1);
}