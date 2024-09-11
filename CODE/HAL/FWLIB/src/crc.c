/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/****************************************************************************/
/** \file crc.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "crc.h"
/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/


/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/*****************************************************************************
 ** \brief	CRC_Input
 **			CRC 输入需要运算的8 位数据
 ** \param [in] data
 ** \return  none
 ** \note	
*****************************************************************************/
void CRC_Input(uint32_t data)
{
	CRC->CRCIN = (uint8_t)data;
}

/*****************************************************************************
 ** \brief	CRC_Output
 **			CRC 输出运算的16位结果
 ** \param [in] none
 ** \return 16 bits Result
 ** \note	
*****************************************************************************/
uint32_t  CRC_Output(void)
{
	return((uint16_t)CRC->CRCD);
}

/*****************************************************************************
 ** \brief	CRC_Reset
 **			CRC复位
 ** \param [in] none
 ** \return none
 ** \note	
*****************************************************************************/
void CRC_Reset(void)
{
	CRC->CRCD = 0;
}
