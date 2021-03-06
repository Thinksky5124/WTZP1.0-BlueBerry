/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Time.c
** 文件说明：   定时器管理（目前只有定时器1）
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "Time.h"

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： InitTime1()
** 函数说明： 启动定时器1
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitTime1()
{
	AUXR &= ~(1<<0); //0-选择定时器1, 1-选择定时器2 AUXR |= (1<<0);
	TMOD = (TMOD&0x0F)|0x00; //定时器1为模式0,16位自动重装
	AUXR |= (1<<6); //12分频设置
  TH1 = 0xFD;
	TL1 = 0x8F;	//baud:9600 fosc=24M
	TR1=1;
}