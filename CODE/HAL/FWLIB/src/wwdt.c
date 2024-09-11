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
/** \file wwdt.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "wwdt.h"
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
 ** \brief	 WWDT_Start
 **			 ����WWDTģ��
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void WWDT_Start(void)
{
	WWDT->CON |= WWDT_WWDTCON_WWDTEN_Msk;
}
/*****************************************************************************
 ** \brief	 WWDT_Stop
 **			 �ر�WWDTģ��
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void WWDT_Stop(void)
{
	WWDT->CON &= ~(WWDT_WWDTCON_WWDTEN_Msk);
}

/*****************************************************************************
 ** \brief	WWDT_ConfigClk
 **			 ����WWDTʱ��
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
 ** \note	WWDT ��������0x3F ������0 ʱ�����ʱ�䣺(PSCSEL*1024*64)*TAPBCLK
*****************************************************************************/
void WWDT_ConfigClk(uint32_t ClkDiv)
{
	WWDT->CON &= ~(WWDT_WWDTCON_PSCSEL_Msk);
	WWDT->CON |= (ClkDiv);
}
/*****************************************************************************
 ** \brief	 WWDT_ConfigCompare
 **			 ����WWDT�Ƚ�ֵ
 ** \param [in] Compare: 6BitValue
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_ConfigCompare(uint32_t Compare)
{
	WWDT->CON &= ~(WWDT_WWDTCON_CMPDAT_Msk);
	WWDT->CON |= ( (Compare & 0x3f) << WWDT_WWDTCON_CMPDAT_Pos);	
}

/*****************************************************************************
 ** \brief	 WWDT_EnableCompareInt
 **			 ����WWDT�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_EnableCompareInt(void)
{
	WWDT->CON |= WWDT_WWDTCON_WWDTIEN_Msk;	
}

/*****************************************************************************
 ** \brief	 WWDT_DisableCompareInt
 **			 �ر�WWDT�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void WWDT_DisableCompareInt(void)
{
	WWDT->CON &= ~(WWDT_WWDTCON_WWDTIEN_Msk);	
}

/*****************************************************************************
 ** \brief	 WWDT_GetCompareIntFlag
 **			 ��ȡWWDTʹ�ܲ������жϱ�־
 ** \param [in] none
 ** \return  1:ʹ���жϲ������ж� 0�����ж�
 ** \note	 
*****************************************************************************/
uint32_t WWDT_GetCompareIntFlag(void)
{
	return((WWDT->MIS & WWDT_WWDTMIS_WWDTMIS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	 WWDT_ClearCompareIntFlag
 **			 ���WWDT�жϱ�־
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WWDT_ClearCompareIntFlag(void)
{
	WWDT->ICLR |= WWDT_WWDTICLR_WWDTICLR_Msk;
}

/*****************************************************************************
 ** \brief	 WWDT_GetTimingData
 **			 ��ȡWWDT����ֵ
 ** \param [in] none
 ** \return 6bit value
 ** \note	 
*****************************************************************************/
uint32_t WWDT_GetTimingData(void)
{
	return(0x3f & WWDT->VAL);
}

/*****************************************************************************
 ** \brief	 WWDT_Reload
 **			 ����WWDT
 ** \param [in] none
 ** \return none
 ** \note	 
*****************************************************************************/
void WWDT_Reload(void)
{
	WWDT->RL = WWDT_RL_WRITE_KEY;
}

