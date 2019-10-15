#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int
#define FOSC 11059200L							// ����Ƶ��11.0592MHz(s)
#define CYCLE (12000000.0/FOSC)			// ϵͳ��������(us) 
#define SHOWDALAY 6

sbit DAT = P3^0;										// 74HC164 ��������˿�
sbit CLK = P3^1;										// 74HC164 ʱ������˿�

//��������ܶ�ѡ(����С����0~9��'-')
unsigned char code table1[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xfe};


/**********************************************************
*  �������ƣ�12us�߾�����ʱ����(12.04us)(11.0592MHz)
*  ���ڣ�2019-10-4
*  ������ZhangHJ
*  ˵����Ƕ��ѭ����ʱ,��ʱ12.04us����ʾ��������
***********************************************************/
void delay_12us()
{
	int i;
	i++;i++;
}



/**********************************************************
*  �������ƣ��;�����ʱ����
*  ���ڣ�2019-9-7
*  ������ZhangHJ
*  ˵����Ƕ��ѭ����ʱ
***********************************************************/
void delay(unsigned int mstime)
{
	int i,j;
	for(i=mstime; i>=0; i--)
		for(j=114; j>=0; j--);
}



/**********************************************************
*  �������ƣ�74HC164����Byte����
*  ���ڣ�2019-9-29
*  ������ZhangHJ
*  ˵����74HC164��λ�Ĵ�������һ�ֽ����ݷ����Ĵ���
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=table1[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;					// ����һ��������
		CLK=1;
		num>>=1;				// �����ݷ��͵��Ĵ���
	}
}



/**********************************************************
*  �������ƣ������������ʾ����
*  �޸����ڣ�2019-10-9
*  �޸��ˣ�ZhangHJ
*  ˵����1.dist��ʾ��Ҫ��ʾ����ֵ(��/ǧλ��ֵ)
*				 2.A0��A1��A2��A3�ֱ�Ϊ��λ��ʮλ����λ��С��λ����ֵ
***********************************************************/
void display(uint dist)				// ��ʾ����
{
	uchar A0,A1t,A1,A2t,A2,A3;
	A0 = dist/1000;							// A0 --> ǧλ
	A1t = dist/100;							// A1t --> ǰ��λ
	A1 = A1t%10;								// A1 --> ��λ
	A2t = dist%100;							// A2t --> ����λ
	A2 = A2t/10;								// A2 --> ʮλ
	A3 = dist%10;								// A3 --> ��λ
	
	// �����������ʾ�¶���ֵ
	P1 |= 0x0f;
	SendByte_74HC164(A0);
	P1 &= 0xf7;									// 0111
	delay(SHOWDALAY);
	P1 |= 0x0f;

	SendByte_74HC164(A1);
	P1 &= 0xfB;									// 1011
	delay(SHOWDALAY);
	P1 |= 0x0f;
	
	SendByte_74HC164(A2);
	P1 &= 0xfD;									// 1101
	delay(SHOWDALAY);
	P1 |= 0x0f;
	
	SendByte_74HC164(A3);
	P1 &= 0xfE;									// 1110
	delay(SHOWDALAY);
	P1 |= 0x0f;
}




/**********************************************************
*  �������ƣ���ʱ���������ڲ��Ժ���
*  �޸����ڣ�2019-10-11
*  �޸��ˣ�ZhangHJ
*  ˵����1. ��ʼ����ʱģʽ,���жϼ�ʱ
*				 2. ��ʱ12us,�رռ�ʱ
*				 3. ��ȷ�Ļ�����ֵӦ���� 11
***********************************************************/
uint GetCount()
{
	uint count = 0;
	
	TMOD = 0x01;											// ��ʱ��0��ʽ1	(16λ������,TL0��TH0ȫ��)
	TH0 = TL0 = 0;										// װ���ֵ

	TR0 = 1;													// ���ж�,��ʼ��ʱ����
	delay_12us();											// ��ʱ12us
	TR0 = 0;													// �ر��ж�
	count = (TH0 << 8) | TL0;					// ��ȡ16λ��ʱ���������
	return count;											// ���ؼ�������
}



// ����������: ����һ�μ�ʱ����������
void main()
{
	uint dis;
	uint i;
	delay(200);												// ��ʼ���ȴ�
	
	while(1)
	{
		dis = GetCount();								// ��ʼ����ʱ��
		for(i=200; i>0; i--)
		{
			display(dis);									// ѭ����ʾ����ֵ
		}
	}
}

