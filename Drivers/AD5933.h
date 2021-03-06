/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   AD5933.h
** 文件说明：   AD5933的驱动程序头文件
*****************************************************************/
#ifndef AD5933_H
#define AD5933_H

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include "I2C.h"

/*---------------------DEFINES-----------------------*/


/*---------------------DECLARES----------------------*/

void AD5933WriteByte(uint8 Addr,uint8 dat);
void AD5933SetPointer(uint8 Addr);
uint8 AD5933Read(uint8 Addr);

#endif