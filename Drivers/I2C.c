/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-08
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   I2C.c
** �ļ�˵����   ���õ�Ƭ����I2Cͨ��ģ�飨Ŀǰֻ�ж˿�3��
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "I2C.h"

/*---------------------VARIABLES---------------------*/


/*---------------------FUNCTIONS---------------------*/
void InitI2C()
{
	P_SW2=P_SW2|0X30;
	I2CCFG = 0xe0;                              //ʹ��I2C����
   I2CMSST = 0x00;
}

void Wait()
{
	while(!(I2CMSST&0x40));
	I2CMSST&=~0x40;
}

void Start()
{
	I2CMSCR=0x01;
	Wait();
}

void SendData(unsigned char dat)
{
	I2CTXD=dat;
	I2CMSCR=0x02;
	Wait();
}

void RecvACK()
{
	I2CMSCR=0x03;
	Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                             //����RECV����
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                             //����ACK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                             //����NCK�ź�
    I2CMSCR = 0x05;                             //����ACK�ź�
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                             //����STOP����
    Wait();
}

void Delay()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

void I2C_AD5933()
{
    Start();                                    //������ʼ����
    SendData(0xa0);                             //�����豸���д����
    RecvACK();
    SendData(0x00);                             //���ʹ洢����ַ���ֽ�
    RecvACK();
    SendData(0x00);                             //���ʹ洢����ַ���ֽ�
    RecvACK();
    SendData(0x12);                             //д����
    RecvACK();
    Stop();                                     //����ֹͣ����

    Delay();                                    //�ȴ��豸д����

    Start();                                    //������ʼ����
    SendData(0xa0);                             //
    RecvACK();
    SendData(0x00);                             //?????????
    RecvACK();
    SendData(0x00);                             //?????????
    RecvACK();
    Start();                                    //??????
    SendData(0xa1);                             //??????+???
    RecvACK();
    P0 = RecvData();                            //????1
    SendACK();
    P2 = RecvData();                            //????2
    SendNAK();
    Stop();                                     //??????

    P_SW2 = 0x00;

    while (1);
}