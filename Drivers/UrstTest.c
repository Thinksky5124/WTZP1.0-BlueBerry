/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   UrstTest.c
** 文件说明：   串口异步通讯（目前只有串口1）
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "UrstTest.h"

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： UartIsr()
** 函数说明： 串口1中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
/*
void UartIsr() interrupt 4 using 1
{
	if(TI)
	{
		TI=0;
	}
	if(RI)
	{
		RI=0;
	}
} */
/***********************************************************************
** 函 数 名： InitUart1()
** 函数说明： 串口1异步通信初始化程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitUart1()
{
	SCON = 0x50; //(0101 0000) 工作方式为方式1,允许接收
	AUXR &= ~(1<<0); //0-选择定时器1, 1-选择定时器2 AUXR |= (1<<0);
	TMOD = (TMOD&0x0F)|0x00; //定时器1为模式0,16位自动重装
	AUXR |= (1<<6); //12分频设置
  TH1 = 0xFD;
	TL1 = 0x8F;	//baud:9600 fosc=24M
	TR1=1;																																	
}
/***********************************************************************
** 函 数 名： UartSend(unsigned char dat)
** 函数说明： 单字节发送程序
**---------------------------------------------------------------------
** 输入参数： uint8
** 返回参数： 无
***********************************************************************/
//
void UartSend(unsigned char dat)
{
	SBUF=dat;
	while(!TI);
	TI=0;
}
/***********************************************************************
** 函 数 名： UartSend_Byte(unsigned long int dat,unsigned char n)
** 函数说明： 多字节发送程序//先送低8位再送高8位
**---------------------------------------------------------------------
** 输入参数： uint32（发送数据），uint8（发送数据字节数）
** 返回参数： 无
***********************************************************************/
void UartSend_Byte(unsigned long int dat,unsigned char n) 
{
	unsigned char i,ch;
	for(i=0;i<n;i++)
	{
		ch=dat;
		UartSend(ch);
		dat=dat>>8;
	}
}