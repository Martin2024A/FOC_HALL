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
/** \file wdt.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "wdt.h"
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
 ** \brief	 WDT_EnableRestSystem
 **			 ����WDT�����λϵͳ
 ** \param [in] none
 ** \return  none
 ** \note	(1)ʹ��WDT ��λ��������WDT �жϺ�û�����жϱ�־λ���´η���WDT�ж�ʱ����WDT��λ.
 **			(2)��ʹ�ܸ�λʱ������ʹ��WDT�ж�.
*****************************************************************************/
void WDT_EnableRestSystem(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->CON &= ~(WDT_WDTCON_WDTEN_Msk);
	WDT->LOCK = 0x0;	
}
/*****************************************************************************
 ** \brief	 WDT_DisableRestSystem
 **			 �ر�WDT�����λϵͳ
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void WDT_DisableRestSystem(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->CON &= ~(WDT_WDTCON_WDTEN_Msk);
	WDT->CON |= (WDT_CON_WRITE_KEY);
	WDT->LOCK = 0x0;		
}

/*****************************************************************************
 ** \brief	 WDT_ConfigClk
 **			 ����WDTʱ��
 ** \param [in] ClkDiv: (1)WDT_CLK_DIV_1   
 **						(2)WDT_CLK_DIV_16  
 **						(3)WDT_CLK_DIV_256 
 ** \return  none
 ** \note	
*****************************************************************************/
void WDT_ConfigClk(uint32_t ClkDiv)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->CON &= ~(WDT_WDTCON_WDTPRE_Msk);
	WDT->CON |= (ClkDiv);
	WDT->LOCK = 0x0;		
}
/*****************************************************************************
 ** \brief	 WDT_ConfigPeriod
 **			 ����WDT�������
 ** \param [in] Period: 32BitValue
 ** \return  none
 ** \note	 
*****************************************************************************/
void WDT_ConfigPeriod(uint32_t Period)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->LOAD = Period;
	WDT->LOCK = 0x0;	
}

/*****************************************************************************
 ** \brief	 WDT_EnableOverflowInt
 **			 ����WDT����ж�
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WDT_EnableOverflowInt(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->CON |= WDT_WDTCON_WDTIEN_Msk;
	WDT->LOCK = 0x0;			
}


/*****************************************************************************
 ** \brief	 WDT_DisableOverflowInt
 **			 �ر�WDT����ж�
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WDT_DisableOverflowInt(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->CON &= ~(WDT_WDTCON_WDTIEN_Msk);
	WDT->LOCK = 0x0;
}

/*****************************************************************************
 ** \brief	 WDT_GetOverflowIntFlag
 **			 ��ȡWDTʹ�ܲ������жϱ�־
 ** \param [in] none
 ** \return  1:ʹ���жϲ������ж� 0�����ж�
 ** \note	 
*****************************************************************************/
uint32_t WDT_GetOverflowIntFlag(void)
{
	return((WDT->MIS & WDT_WDTMIS_WDTMIS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 WDT_ClearOverflowIntFlag
 **			 ���WDT�жϱ�־�����¼��س�ֵ
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WDT_ClearOverflowIntFlag(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->ICLR = WDT_ICLR_WRITE_KEY;
	WDT->LOCK = 0x0;
}

/*****************************************************************************
 ** \brief	 WDT_GetTimingData
 **			 ��ȡWDT����ֵ
 ** \param [in] none
 ** \return 32bit value
 ** \note	 
*****************************************************************************/
uint32_t WDT_GetTimingData(void)
{
	return(WDT->VAL);
}

/*****************************************************************************
 ** \brief	 WDT_ClearWDT
 **			 ι��
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WDT_ClearWDT(void)
{
	WDT->LOCK = WDT_LOCK_WRITE_KEY;
	WDT->ICLR = WDT_ICLR_WRITE_KEY;
	WDT->LOCK = 0x0;
}

