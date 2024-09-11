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
/** \file wwdt.h
**
** History:
** 
*****************************************************************************/
#ifndef __WWDT_H__
#define __WWDT_H__

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
 **WWDT 时钟
-----------------------------------------------------------------------------*/
#define		WWDT_CLK_DIV_2			(0x00UL)		/*Fwwd = FAPB / 2*/
#define		WWDT_CLK_DIV_4			(0x01UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 4*/		
#define		WWDT_CLK_DIV_8			(0x02UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 8*/		
#define		WWDT_CLK_DIV_16			(0x03UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 16*/
#define		WWDT_CLK_DIV_32			(0x04UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 32*/
#define		WWDT_CLK_DIV_64			(0x05UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 64*/
#define		WWDT_CLK_DIV_128		(0x06UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 128*/	
#define		WWDT_CLK_DIV_256		(0x07UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 256*/
#define		WWDT_CLK_DIV_512		(0x08UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 512*/
#define		WWDT_CLK_DIV_1024		(0x09UL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 512*/
#define		WWDT_CLK_DIV_2048		(0x0aUL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 2048*/
#define		WWDT_CLK_DIV_4096		(0x0bUL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 4096*/
#define		WWDT_CLK_DIV_8192		(0x0cUL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 8192*/
#define		WWDT_CLK_DIV_16384		(0x0dUL<<WWDT_WWDTCON_PSCSEL_Pos)	/*Fwwd = FAPB / 16384*/
/*----------------------------------------------------------------------------
 **WWDT 重载
-----------------------------------------------------------------------------*/
#define		WWDT_RL_WRITE_KEY		(0x55AAUL)

/*****************************************************************************
 ** \brief	WWDT_ENABLE_DEBUG
 **			WWDT在DEBUG模式中使能
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
#define		WWDT_ENABLE_DEBUG()	do{\
									WWDT->CON |= WWDT_WWDTCON_DEBUG_Msk;\
								}while(0)
/*****************************************************************************
 ** \brief	WWDT_DISABLE_DEBUG
 **			WWDT在DEBUG模式中关闭
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
#define		WWDT_DISABLE_DEBUG() do{\
									WWDT->CON &= ~(WWDT_WWDTCON_DEBUG_Msk);\
								}while(0)

/*****************************************************************************
 ** \brief	WWDT_GET_RIS_FLAG
 **			获取WWDT中断源状态
 ** \param [in] none
 ** \return  1:产生WWDT向下溢出中断 0：无中断
 ** \note	 
*****************************************************************************/
#define		WWDT_GET_RIS_FLAG()	(((WWDT->RIS & WWDT_WWDTRIS_WWDTRIS_Msk)? 1:0))
							
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
 ** \brief	 WWDT_Start
 **			 开启WWDT模块
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void WWDT_Start(void);
/*****************************************************************************
 ** \brief	 WWDT_Stop
 **			 关闭WWDT模块
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void WWDT_Stop(void);

/*****************************************************************************
 ** \brief	WWDT_ConfigClk
 **			 配置WWDT时钟
 ** \param [in] ClkDiv: (1)WWDT_CLK_DIV_2   
 **						(2)WWDT_CLK_DIV_4  
 **						(3)WWDT_CLK_DIV_8 
 **						(4)WWDT_CLK_DIV_16  
 **						(5)WWDT_CLK_DIV_32
 **						(6)WWDT_CLK_DIV_64  
 **						(7)WWDT_CLK_DIV_128 
 **						(8)WWDT_CLK_DIV_256  
 **						(9)WWDT_CLK_DIV_512 
 **						(10)WWDT_CLK_DIV_1024  
 **						(11)WWDT_CLK_DIV_2048 
 **						(12)WWDT_CLK_DIV_4096  
 **						(13)WWDT_CLK_DIV_8192 
 **						(14)WWDT_CLK_DIV_16384  
 ** \return  none
 ** \note	WWDT 计数器从0x3F 计数到0 时溢出的时间：(PSCSEL*1024*64)*TAPBCLK
*****************************************************************************/
void WWDT_ConfigClk(uint32_t ClkDiv);
/*****************************************************************************
 ** \brief	 WWDT_ConfigCompare
 **			 配置WWDT比较值
 ** \param [in] Compare: 6BitValue
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_ConfigCompare(uint32_t Compare);

/*****************************************************************************
 ** \brief	 WWDT_EnableCompareInt
 **			 开启WWDT比较中断
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_EnableCompareInt(void);

/*****************************************************************************
 ** \brief	 WWDT_DisableCompareInt
 **			 关闭WWDT比较中断
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_DisableCompareInt(void);

/*****************************************************************************
 ** \brief	 WWDT_GetCompareIntFlag
 **			 获取WWDT使能并产生中断标志
 ** \param [in] none
 ** \return  1:使能中断并产生中断 0：无中断
 ** \note	 
*****************************************************************************/
uint32_t WWDT_GetCompareIntFlag(void);
/*****************************************************************************
 ** \brief	 WWDT_ClearCompareIntFlag
 **			 清除WWDT中断标志
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WWDT_ClearCompareIntFlag(void);

/*****************************************************************************
 ** \brief	 WWDT_GetTimingData
 **			 获取WWDT计数值
 ** \param [in] none
 ** \return 6bit value
 ** \note	 
*****************************************************************************/
uint32_t WWDT_GetTimingData(void);

/*****************************************************************************
 ** \brief	 WWDT_Reload
 **			 重载WWDT
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WWDT_Reload(void);



#ifdef __cplusplus
}
#endif

#endif /* __WWDT_H__ */

