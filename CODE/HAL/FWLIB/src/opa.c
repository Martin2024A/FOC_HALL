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
/** \file opa.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "opa.h"
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
 ** \brief	 OPA_ConfigRunMode
 **			 设置运放运行模式
 ** \param [in] opa :OPA0 、OPA1
 **				mode: (1)OPA_FIL_CMP
 **					  (2)OPA_FIL_OPA
 ** \return  none
 ** \note    
 *****************************************************************************/
void OPA_ConfigRunMode(OP_Type *opa, uint32_t mode)
{
	opa->CON0 &= ~(OPA_CON0_FIL_Msk);
	opa->CON0 |= mode;		
}

/*****************************************************************************
 ** \brief	 OPA_ConfigPositive
 **			 设置运放正端输入
 ** \param [in] opa :OPA0 、OPA1
 **				PositiveSource:  (1)OPA_POSSEL_P	:OPnP
 **								 (2)OPA_POSSEL_1P2 
 ** \return  none
 ** \note    默认关闭运放模块
 *****************************************************************************/
void OPA_ConfigPositive(OP_Type *opa, uint32_t PositiveSource)
{
	opa->CON0 &= ~(OPA_CON0_EN_Msk|OPA_CON0_PS_Msk);
	opa->CON0 |= PositiveSource;
}

/*****************************************************************************
 ** \brief	 OPA_ConfigNegative
 **			 设置比较器负端输入
 ** \param [in] opa :OPA0 、OPA1
 **				NegativeSource:  (1)OPA_NEGSEL_N		:OPnN			
 ** \return  none
 ** \note   默认关闭运放模块
 *****************************************************************************/
void OPA_ConfigNegative(OP_Type *opa, uint32_t NegativeSource)
{
	opa->CON0 &= ~(OPA_CON0_EN_Msk|OPA_CON0_NS_Msk);
	opa->CON0 |= NegativeSource;
}

/*****************************************************************************
 ** \brief	 OPA_ConfigOutput
 **			 设置比较器输出端
 ** \param [in] opa :OPA0 、OPA1
 **				OutSource:	OPA_OUTSEL_O
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_ConfigOutput(OP_Type *opa,uint32_t OutSource)
{
	opa->CON0 &= ~(OPA_CON0_EN_Msk|OPA_CON0_OS_Msk);
	opa->CON0 |= OutSource;
}


/********************************************************************************
 ** \brief	 OPA_Start
 **			 开启OP
 ** \param [in] opa :OPA0 、OPA1
 ** \return  none
 ** \note   
 ******************************************************************************/
void OPA_Start(OP_Type *opa)
{
	opa->CON0 |= OPA_CON0_EN_Msk;
}

/********************************************************************************
 ** \brief	 OPA_Stop
 **			 关闭OP
 ** \param [in] opa :OPA0 、OPA1
 ** \return  none
 ** \note   
 ******************************************************************************/
void OPA_Stop(OP_Type *opa)
{
	opa->CON0 &= ~(OPA_CON0_EN_Msk);
}

/********************************************************************************
 ** \brief	 OPA_GetResult
 **			 获取比较器值
 ** \param [in] opa :OPA0 、OPA1
 ** \return  0/1
 ** \note   只适用于调试模式
 ******************************************************************************/
uint32_t OPA_GetResult(OP_Type *opa)
{
	return((opa->CON1 & OPA_CON1_OUT_Msk)? 1:0);
}

/*****************************************************************************
 ** \brief	OPA_EnableAdjustMode
 **			 开启运放调节模式
 ** \param [in] opa :OPA0 、OPA1
 **				AdjustTarget:    (1)OPA_ADJ_SEL_N		:调节作用于负端输入		
 **								 (2)OPA_ADJ_SEL_P		:调节作用于正端输入	
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_EnableAdjustMode(OP_Type *opa, uint32_t AdjustTarget)
{
	opa->CON1 &= ~(OPA_CON1_CRS_Msk);	
	opa->CON1 |= (AdjustTarget);
	opa->CON0 |= OPA_CON0_COFM_Msk;
}

/*****************************************************************************
 ** \brief	OPA_DisableAdjustMode
 **			 关闭运放调节模式
 ** \param [in] opa :OPA0 、OPA1
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_DisableAdjustMode(OP_Type *opa)
{
	opa->CON0 &= ~(OPA_CON0_COFM_Msk);
}

/*****************************************************************************
 ** \brief	OPA_EnableConfigAdjust
 **			 开启运放Config调节
 ** \param [in] opa :OPA0 、OPA1
 ** \return  none
 ** \note    使用Config调节值
 *****************************************************************************/
void OPA_EnableConfigAdjust(OP_Type *opa)
{
	opa->ADJE = OPA_ADJ_USE_CONFIG;
}

/*****************************************************************************
 ** \brief	OPA_EnableOPADJAdjust
 **			 开启运放OPADJ调节
 ** \param [in] opa :OPA0 、OPA1
 **				AdjustValue: 0x00 ~ 0x1f
 ** \return  none
 ** \note    使用OPnADJ寄存器中的OPnADJ<4:0>
 *****************************************************************************/
void OPA_EnableOPADJAdjust(OP_Type *opa, uint32_t AdjustValue)
{
	opa->CON1 &= ~(OPA_CON1_ADJ_Msk);
	opa->CON1 |= AdjustValue & 0x1f;
	opa->ADJE = OPA_ADJ_USE_OPADJ;
}

/*****************************************************************************
 ** \brief	OPA_GetAutoAdjustResult
 **			 获取运放调节模式结果
 ** \param [in] opa :OPA0 、OPA1
 ** \return  Result
 ** \note    
 *****************************************************************************/
uint32_t  OPA_GetAutoAdjustResult(OP_Type *opa)
{
	uint32_t AdjVlue, WaitTime, AdjResult;
	OPA_EnableAdjustMode(opa,OPA_ADJ_SEL_P);		/*开启运放, 使用正端输入调节*/
	opa->ADJE = OPA_ADJ_USE_OPADJ;		
	opa->CON1 &= ~(OPA_CON1_ADJ_Msk);
	OPA_Start(opa);									/*开启OPA*/
	for(WaitTime=100; WaitTime>0;WaitTime--);	
	
	AdjResult = OPA_GetResult(opa);
	for(AdjVlue=0; AdjVlue<32;AdjVlue++)
	{
		opa->CON1 |= AdjVlue;
		for(WaitTime=100; WaitTime>0;WaitTime--);	
		if(AdjResult != OPA_GetResult(opa))
		{
			OPA_DisableAdjustMode(opa);
			OPA_Stop(opa);		
			return AdjVlue;
		}
	}
	return 0x10;
}


