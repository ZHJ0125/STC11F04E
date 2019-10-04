#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define dec(dat) ((dat>>4)*10+(dat&0x0f)) 		// BCD��תʮ����

sbit IO = P1^4;					// DS1302 �������������
sbit RST = P1^6;				// DS1302 ��λ�ź���
sbit SCLK = P1^5;				// DS1302 ʱ���ź���
sbit DS = P1^7;					// DS18B20 ���ݶ˿�
sbit DAT = P3^0;				// 74HC164 ��������˿�
sbit CLK = P3^1;				// 74HC164 ʱ������˿�
sbit DP = P3^7;					// ʱ��ָ��
uint flag = 0;					// С������˸����

uchar code write_addr[]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};		// DS1302д��ַ
uchar code read_addr[]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};		// DS1302����ַ

// ��������ܶ�ѡ(����С����0~9)
uchar code table1[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82};

// �洢˳�������ʱ��������,�洢��ʽ����BCD��
uchar time[7]={0,0x55,0x18,0x04,0x10,0x05,0x19};  //��ʼ����ʱ��Ϊ2019��10��4��18:55:00


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
*  �������ƣ�DS1302д��������
*  ���ڣ�2019-10-4
*  ������ZhangHJ
*  ˵����д����������������,add��ʾҪд��ĵ�ַ;wdata��ʾҪд�������
*				 1. ��д������Ҫ�Ƚ�RST���߲��ܽ���
*				 2. ��д������ֽ�,��ʱ�������ش���д������
*				 3. ��д�������ֽ�,ͬ����ʱ��������д������
*				 4. �������RST��ֹ���ݴ���
***********************************************************/
void DS1302Write(uchar add,uchar wdata)
{
	uchar a;
	//wdata = hex(wdata);		// ת��ΪBCD��
	RST=0;									// ����RST����,��ֹ���ݴ���
	SCLK=0;									// ����SCLK����,����ʱ����
	RST=1;									// ����RST����,�������ݴ��䶼Ҫ����RST��,���������߼�
	//��д������ֽ�
	for(a=0; a<8; a++)
	{
			IO= add & 0x01;			// IO����׼����Ҫд���1λ����
			SCLK=1;							// SCLK������,1λ���ݴ�IO��д��,��λ��д��
			add>>=1;						// ��������1λ
			SCLK=0;							// ����SCLK,Ϊ�´�д��׼��,ѭ��8��д��1�ֽ�
	}
	//��д�������ֽ�
	for(a=0; a<8; a++)
	{
			IO= wdata & 0x01;
			SCLK=1;
			wdata>>=1;
			SCLK=0;
	}
	RST=0;									// ���ݴ���������RST
}  



/**********************************************************
*  �������ƣ�DS1302����������
*  ���ڣ�2019-10-4
*  ������ZhangHJ
*  ˵����������ֻ��һ������,����Ҫ��ȡ�ļĴ�����ַadd
*				 1. ������Ҫ����Ҫ��ȡ�ĵ�ַ(1Byte)д��Ĵ���,�������ؽ���д�����
*				 2. ֮���ȡ�õ�ַ�е�����,���½��ض�ȡ����
*				 3. ��󷵻ض�ȡ����1Byte����
***********************************************************/ 
uchar DS1302Read(uchar add)
{
	uchar a, rdata=0;
	RST = 0;											// ����RST����,��ֹ���ݴ���
	SCLK = 0;											// ����SCLK����,����ʱ����
	RST = 1;											// ����RST����,���������߼�
	//���Ϳ����ֽ�
	for(a=0; a<8; a++)
	{
		SCLK = 0;
		IO = add & 0x01;
		SCLK = 1;										// ����һ��������,д���ַ
		add >>= 1;
	}
	//��1�ֽ�����
	for(a=0; a<8; a++)
	{
		SCLK = 1;
		rdata >>= 1;
		SCLK = 0;										// ����һ���½���,��ȡ����
		if(IO)
		{														// �������1
			rdata |= 0x80;						// �����λ��Ϊ1,��¼��rdata��
		}
	}
	RST=0;												// ����RST
	//return dec(d);        			// ��ȡ������ת����ʮ����
	return rdata;
}



/**********************************************************
*  �������ƣ�DS1302��ʼ������
*  ���ڣ�2019-10-4
*  ������ZhangHJ
*  ˵������ʼ����Ϊ��DS1302��ʼ���ݵ�д��
*				 1. ������Ҫ�ر�д����,����������д��
*				 2. ֮��"���ʱ��������"��˳��д���ʼ����
*				 3. �����д����,��ֹ����д��
***********************************************************/ 
void ds1302_init()
{
   uchar k;
   DS1302Write(0x8e,0x00);  		// ��ֹд����������������д��
   for(k=0;k<7;k++)							// д��7���ֽڵ�ʱ���źţ����ʱ��������
   {
     DS1302Write(write_addr[k],time[k]);
   }
   DS1302Write(0x8e,0x80);  		// ��д����,��ֹ����д��
}




/**********************************************************
*  �������ƣ�DS1302���ݶ�ȡ����
*  ���ڣ�2019-10-4
*  ������ZhangHJ
*  ˵�������ݶ�ȡ��Ϊ���Ĵ�����ַ��ȡ���ݵĹ���
*				 ֱ�Ӱ���ַ��ȡ�Ĵ����е�����,Ȼ�����ݷŵ�time�����ﱣ�漴��
***********************************************************/ 
void read_time()
{
   uchar n;
   for(n=0;n<7;n++)
    time[n]=DS1302Read(read_addr[n]);   //��ȡ���ʱ��������
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
*  �������ƣ������ʱ��������ʾ����
*  �޸����ڣ�2019-10-4
*  �޸��ˣ�ZhangHJ
*  ˵����1.	A0~A9��ʾ���뵽�µ�ʱ����ֵ,���˹��ɿ��Լ��㵽��
*				 2.	DP��ʾʱ��ָ��С����,�͵�ƽѡ��
*				 3.	���ͨ������λѡ�Ͷ�ѡ���������,��ʾʱ��
***********************************************************/
void display()									// ��ʾ����
{
	uchar A0,A1,A2,A3,A4,A5,A6,A7,A8,A9;
	A0 = dec(time[0])/10;					// A0-->��ʮλ
	A1 = dec(time[0])%10;					// A1-->���λ
	A2 = dec(time[1])/10;					// A2-->��ʮλ
	A3 = dec(time[1])%10;					// A3-->�ָ�λ
	A4 = dec(time[2])/10;					// A4-->ʱʮλ
	A5 = dec(time[2])%10;					// A5-->ʱ��λ
	A6 = dec(time[3])/10;					// A6-->��ʮλ
	A7 = dec(time[3])%10;					// A7-->�ո�λ
	A8 = dec(time[3])/10;					// A8-->��ʮλ
	A9 = dec(time[3])%10;					// A9-->�¸�λ
	
	// DP = 0;										// ��ָ�
	flag ++;											// ʱ�����˸����
	if(flag >= 134)
	{
		DP = ~DP;
		flag = 0;
	}
   
	// �����������ʾ�¶���ֵ
	P1 |= 0x0f;
	SendByte_74HC164(A4);					// A4-->ʱʮλ
	P1 &= 0xf7;
	delay(6);
	P1 |= 0x0f;
	
	SendByte_74HC164(A5);					// A5-->ʱ��λ
	P1 &= 0xfB;
	delay(6);
	P1 |= 0x0f;
	
	SendByte_74HC164(A2);					// A2-->��ʮλ
	P1 &= 0xfd;
	delay(6);
	P1 |= 0x0f;
	
	SendByte_74HC164(A3);					// A3-->�ָ�λ
	P1 &= 0xfe;
	delay(6);
	P1 |= 0x0f;
}


// ���������ܣ����ó�ʼʱ��Ϊ��2019��10��4��18:55:00����������ʾʱ��
void main()
{
	ds1302_init();					// DS1302���ڳ�ʼ��
	while(1)
	{
		read_time();					// DS1302��ȡ��ǰʱ��
		display();						// ��ʾ��ǰʱ��
	}
}