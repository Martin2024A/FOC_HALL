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
/** \file fmc.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "fmc.h"
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
 ** \brief	FMC_EraseAll
 **			FMC 整体擦除
 ** \param [in] none 
 ** \return  none
 ** \note	适用于APROM
*****************************************************************************/
void FMC_EraseAll(void)
{
	__DI;
	FMC->LOCK = FMC_WRITE_KEY;
	FMC->CMD = FMC_CMD_ALL_ERASE;
	FMC->LOCK = 0x00;	
	__EI;
}

/*****************************************************************************
 ** \brief	FMC_ErasePage
 **			FMC 页擦除
 ** \param [in] PageAddr: 
 ** \return  none
 ** \note	
*****************************************************************************/
void FMC_ErasePage(uint32_t PageAddr)
{
	__DI;
	FMC->LOCK = FMC_WRITE_KEY;
	FMC->ADR = PageAddr;
	FMC->CMD = FMC_CMD_PAGE_ERASE;
	FMC->LOCK = 0x00;	
	__EI;
}

/*****************************************************************************
 ** \brief	FMC_Read
 **			FMC 读
 ** \param [in] DataAddr：地址两位必须为0
 ** \return  32位数据
 ** \note	
*****************************************************************************/
uint32_t FMC_Read(uint32_t DataAddr)
{
	uint32_t FlashData;
	FMC->LOCK = FMC_WRITE_KEY;
	FMC->ADR = (DataAddr & 0xFFFFFFFC);
	FMC->CMD = FMC_CMD_READ;
	FlashData = FMC->DAT;
	FMC->LOCK = 0x00;
	return FlashData;
}

/*****************************************************************************
 ** \brief	FMC_Write
 **			FMC 写
 ** \param [in] DataAddr：地址两位必须为0
 **				DataVlue: 32位数据
 ** \return  none
 ** \note	
*****************************************************************************/
void FMC_Write(uint32_t DataAddr, uint32_t DataVlue)
{
	__DI;
	FMC->LOCK = FMC_WRITE_KEY;
	FMC->ADR = (DataAddr & 0xFFFFFFFC);
	FMC->DAT = DataVlue;
	FMC->CMD = FMC_CMD_WRITE;
	FMC->LOCK = 0x00;
	__EI;
}

/*****************************************************************************
 ** \brief	FMC_CRC
 **			FMC CRC校验
 ** \param [in] CRCStartAddr:	  CRC校验起始地址
 **				CRCStopAddr:	  CRC校验结束地址
 ** \return  none
 ** \note	 只适用于APROM区
*****************************************************************************/
uint16_t FMC_CRC(uint32_t CRCStartAddr, uint32_t CRCStopAddr)
{
	uint16_t CrcResult;
	FMC->LOCK = FMC_WRITE_KEY;
	FMC->ADR = CRCStartAddr & 0xFFFFFFFC;
	FMC->CRCEA = CRCStopAddr & 0xFFFFFFFC;
	FMC->CRCIN = 0x00;
	FMC->CRCD = 0x00;
	FMC->CMD = FMC_CMD_CRC;
	CrcResult = FMC->CRCD;	
	FMC->LOCK = 0x00;
	return CrcResult;
}
