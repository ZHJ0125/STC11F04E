#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define DELAY_TIME 6
#define SHOW_LOOP	150

sbit DAT = P3^0;				// 74HC164 数据输入端口
sbit CLK = P3^1;				// 74HC164 时钟输入端口

// 定义数码管段选(0~9、NULL)
uchar code duan[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xff};

// 定义学号
// uchar STUNUM[12]=201723010237;

// 定义显示学号的二维数组
uchar code student[][4]={{10,10,10, 2}, 
												 {10,10, 2, 0},
												 {10, 2, 0, 1},
												 { 2, 0, 1, 7},
												 { 0, 1, 7, 2},
												 { 1, 7, 2, 3},
												 { 7, 2, 3, 0},
												 { 2, 3, 0, 1},
												 { 3, 0, 1, 0},
												 { 0, 1, 0, 2},
												 { 1, 0, 2, 3},
												 { 0, 2, 3, 7},
												 { 2, 3, 7,10},
												 { 3, 7,10,10},
												 { 7,10,10,10},
												 {10,10,10,10}};
//uchar code student[][4]={
//	{duan[10],duan[10],duan[10], STUNUM[0]}, 
//	{duan[10],duan[10], STUNUM[0], STUNUM[1]},
//	{duan[10], STUNUM[0], STUNUM[1], STUNUM[2]},
//	{STUNUM[0], STUNUM[1], STUNUM[2], STUNUM[3]},
//	{STUNUM[1], STUNUM[2], STUNUM[3], STUNUM[4]},
//	{STUNUM[2], STUNUM[3], STUNUM[4], STUNUM[5]},
//	{STUNUM[3], STUNUM[4], STUNUM[5], STUNUM[6]},
//	{STUNUM[4], STUNUM[5], STUNUM[6], STUNUM[7]},
//	{STUNUM[5], STUNUM[6], STUNUM[7], STUNUM[8]},
//	{STUNUM[6], STUNUM[7], STUNUM[8], STUNUM[9]},
//	{STUNUM[7], STUNUM[8], STUNUM[9], STUNUM[10]},
//	{STUNUM[8], STUNUM[9], STUNUM[10], STUNUM[11]},
//	{STUNUM[9], STUNUM[10], STUNUM[11],duan[10]},
//	{STUNUM[10], STUNUM[11],duan[10],duan[10]},
//	{STUNUM[11],duan[10],duan[10],duan[10]},
//	{duan[10],duan[10],duan[10],duan[10]}
//};
										 


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
*  函数名称：74HC164发送Byte数据函数
*  日期：2019-9-29
*  姓名：ZhangHJ
*  说明：74HC164移位寄存器输入一字节数据发给寄存器
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=duan[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;					// 制造一个上升沿
		CLK=1;
		num>>=1;				// 将数据发送到寄存器
	}
}




/**********************************************************
*  函数名称：独立帧显示函数
*  日期：2019-10-15
*  姓名：ZhangHJ
*  说明：实现4个数码管滚动显示学号的效果
* 			 数码管引脚低电平有效,首先关闭位选信号,然后给寄存器发送数据(开启段选),
*				 开启位选控制并延时一段时间以显示数字,最后关闭位选信号清屏.
***********************************************************/
//void test_light_byte1()											// 2
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte2()											// 20
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte3()											// 201
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte4()											// 2017
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte5()											// 0172
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte6()											// 1723
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte7()											// 7230
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte8()											// 2301
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte9()												// 3010
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte10()												// 0102
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte11()												// 1023
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(1);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte12()												// 0237
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(0);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfe;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte13()													// 237
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(2);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfd;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte14()													// 37
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(3);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//	
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xfb;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}
//void test_light_byte15()													// 7
//{
//	P1 |= 0x0f;							// 关掉位选
//	SendByte_74HC164(7);		// 开启段选
//	P1 &= 0xf7;							// 开启位选
//	delay_ms(DELAY_TIME);		// 延时显示
//	P1 |= 0x0f;							// 关掉位选
//}

// 滚动显示学号
//void main()
//{
//	uint i;
//	while(1)
//	{
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte1();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte2();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte3();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte4();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte5();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte6();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte7();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte8();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte9();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte10();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte11();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte12();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte13();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte14();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte15();
//		delay_ms(100);
//	}
//}



/**********************************************************
*  函数名称：数码管显示函数
*  日期：2019-10-15
*  姓名：ZhangHJ
*  说明：控制数码管显示数字
* 			 数码管引脚低电平有效,首先关闭位选信号,然后给寄存器发送数据(开启段选),
*				 开启位选控制并延时一段时间以显示数字,最后关闭位选信号清屏.
***********************************************************/
void test_light(uchar num[])
{
	P1 |= 0x0f;							// 关掉位选
	SendByte_74HC164(num[0]);		// 开启段选
	P1 &= 0xf7;							// 开启位选
	delay_ms(DELAY_TIME);		// 延时显示
	P1 |= 0x0f;							// 关掉位选
	
	SendByte_74HC164(num[1]);		// 开启段选
	P1 &= 0xfb;							// 开启位选
	delay_ms(DELAY_TIME);		// 延时显示
	P1 |= 0x0f;							// 关掉位选
	
	SendByte_74HC164(num[2]);		// 开启段选
	P1 &= 0xfd;							// 开启位选
	delay_ms(DELAY_TIME);		// 延时显示
	P1 |= 0x0f;							// 关掉位选
	
	SendByte_74HC164(num[3]);		// 开启段选
	P1 &= 0xfe;							// 开启位选
	delay_ms(DELAY_TIME);		// 延时显示
	P1 |= 0x0f;							// 关掉位选
}



// 通过二维数组显示滚动数据
void main()
{
	uint i,delay;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			for(delay=120;delay>0;delay--)
				test_light(student[i]);
		}
	}
}






