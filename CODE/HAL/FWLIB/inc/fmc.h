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

/*****************************************************************************/
/** \file fmc.h
**
** History:
** 
*****************************************************************************/
#ifndef __FMC_H_
#define __FMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "CMS32M55xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/

/*----------------------------------------------------------------------------
 **FMC ��������
-----------------------------------------------------------------------------*/
#define	FMC_APROM_START		(0x00UL)		
#define	FMC_APROM_END		(0xFFFFFFFFUL)				/*Max:64Kb*/

#define	FMC_DAT_START		(0x1C000000UL)
#define	FMC_DAT_END			(0x1C0003FFUL)				/*1Kb*/


/*----------------------------------------------------------------------------
 **FMC ��������
-----------------------------------------------------------------------------*/
#define	FMC_CMD_READ		(0x1U)				
#define FMC_CMD_WRITE		(0x2U)				
#define FMC_CMD_CRC			(0xDU)				/*CRCУ�� CRC16-CCITT*/
#define FMC_CMD_PAGE_ERASE		(0x3U)				/*ҳ����*/
#define FMC_CMD_ALL_ERASE		(0x6U)				/*�������*/

/*----------------------------------------------------------------------------
 **FMC ����
-----------------------------------------------------------------------------*/
#define	FMC_WRITE_KEY	(0x55AA6699)


/*****************************************************************************
 ** \brief	FMC_IS_BUSY
 **			FMC ״̬
 ** \param [in] none 
 ** \return 0: ����   1��æ
 ** \note	
*****************************************************************************/
#define	FMC_IS_BUSY()		((FMC->CON&FMC_CON_BUSY_Msk)? 1:0)


/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/*****************************************************************************
 ** \brief	FMC_EraseAll
 **			FMC �������
 ** \param [in] none 
 ** \return  none
 ** \note	������APROM
*****************************************************************************/
void FMC_EraseAll(void);

/*****************************************************************************
 ** \brief	FMC_ErasePage
 **			FMC ҳ����
 ** \param [in] PageAddr: 
 ** \return  none
 ** \note	
*****************************************************************************/
void FMC_ErasePage(uint32_t PageAddr);

/*****************************************************************************
 ** \brief	FMC_Read
 **			FMC ��
 ** \param [in] DataAddr����ַ��λ����Ϊ0
 ** \return  32λ����
 ** \note	
*****************************************************************************/
uint32_t FMC_Read(uint32_t DataAddr);
/*****************************************************************************
 ** \brief	FMC_Write
 **			FMC д
 ** \param [in] DataAddr����ַ��λ����Ϊ0
 **				DataVlue: 32λ����
 ** \return  none
 ** \note	
*****************************************************************************/
void FMC_Write(uint32_t DataAddr, uint32_t DataVlue);

/*****************************************************************************
 ** \brief	FMC_CRC
 **			FMC CRCУ��
 ** \param [in] CRCStartAddr:	  CRCУ����ʼ��ַ
 **				CRCStopAddr:	  CRCУ�������ַ
 ** \return  none
 ** \note	ֻ������APROM��
*****************************************************************************/
uint16_t FMC_CRC(uint32_t CRCStartAddr, uint32_t CRCStopAddr);


#ifdef __cplusplus
}
#endif

#endif /* __FMC_H_ */

