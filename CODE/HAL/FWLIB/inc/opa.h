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
/** \file opa.h
**
** History:
** 
*****************************************************************************/
#ifndef __OPA_H_
#define __OPA_H_

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
 **OPA	����ģʽ
-----------------------------------------------------------------------------*/
#define		OPA_FIL_CMP			(0x01UL<<OPA_CON0_FIL_Pos)	/*�Ƚ�ģʽ*/
#define		OPA_FIL_OPA			(0x00UL)					/*�˷�ģʽ*/
/*----------------------------------------------------------------------------
 **OPA	����ѡ��
-----------------------------------------------------------------------------*/
#define		OPA_POSSEL_P		(0x00UL)					/*ѡ��OPA P*/
#define		OPA_POSSEL_1P2		(0x01UL<<OPA_CON0_PS_Pos)	/*ѡ��1.2V Bandgap*/	
/*----------------------------------------------------------------------------
 **OPA	����ѡ��
-----------------------------------------------------------------------------*/
#define		OPA_NEGSEL_N		(0x00UL)					/*ѡ��OPA N*/
/*----------------------------------------------------------------------------
 **OPA	���ѡ��
-----------------------------------------------------------------------------*/
#define		OPA_OUTSEL_O		(0x01UL<<OPA_CON0_OS_Pos)	/*ѡ��OPA O*/

/*----------------------------------------------------------------------------
 **opa ����
------------------------------------------------------------------------------*/
#define OPA_ADJ_SEL_N			(0x00)		/*opa����ģʽ�����ѡ�񸺶�*/
#define OPA_ADJ_SEL_P			(0x01<<OPA_CON1_CRS_Pos)		/*opa����ģʽ�����ѡ������*/
#define OPA_ADJ_USE_CONFIG		(0xFF)		/*opa����ģʽʧ����ѹ��Config����*/
#define OPA_ADJ_USE_OPADJ		(0xAA)		/*opa����ģʽʧ����ѹ��OPnADJ[4:0]����*/


							
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
 ** \brief	 OPA_ConfigRunMode
 **			 �����˷�����ģʽ
 ** \param [in] opa :OPA0 ��OPA1
 **				mode: (1)OPA_FIL_CMP
 **					  (2)OPA_FIL_OPA
 ** \return  none
 ** \note    
 *****************************************************************************/
void OPA_ConfigRunMode(OP_Type *opa, uint32_t mode);

/*****************************************************************************
 ** \brief	 OPA_ConfigPositive
 **			 �����˷���������
 ** \param [in] opa :OPA0 ��OPA1
 **				PositiveSource:  (1)OPA_POSSEL_P	:OPnP
 **								 (2)OPA_POSSEL_1P2 
 ** \return  none
 ** \note    Ĭ�Ϲر��˷�ģ��
 *****************************************************************************/
void OPA_ConfigPositive(OP_Type *opa, uint32_t PositiveSource);

/*****************************************************************************
 ** \brief	 OPA_ConfigNegative
 **			 ���ñȽ�����������
 ** \param [in] opa :OPA0 ��OPA1
 **				NegativeSource:  (1)OPA_NEGSEL_N		:OPnN			
 ** \return  none
 ** \note   Ĭ�Ϲر��˷�ģ��
 *****************************************************************************/
void OPA_ConfigNegative(OP_Type *opa, uint32_t NegativeSource);

/*****************************************************************************
 ** \brief	 OPA_ConfigOutput
 **			 ���ñȽ��������
 ** \param [in] opa :OPA0 ��OPA1
 **				OutSource:	OPA_OUTSEL_O
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_ConfigOutput(OP_Type *opa,uint32_t OutSource);


/********************************************************************************
 ** \brief	 OPA_Start
 **			 ����OP
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  none
 ** \note   
 ******************************************************************************/
void OPA_Start(OP_Type *opa);

/********************************************************************************
 ** \brief	 OPA_Stop
 **			 �ر�OP
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  none
 ** \note   
 ******************************************************************************/
void OPA_Stop(OP_Type *opa);

/********************************************************************************
 ** \brief	 OPA_GetResult
 **			 ��ȡ�Ƚ���ֵ
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  0/1
 ** \note   ֻ�����ڵ���ģʽ
 ******************************************************************************/
uint32_t OPA_GetResult(OP_Type *opa);

/*****************************************************************************
 ** \brief	OPA_EnableAdjustMode
 **			 �����˷ŵ���ģʽ
 ** \param [in] opa :OPA0 ��OPA1
 **				AdjustTarget:    (1)OPA_ADJ_SEL_N		:���������ڸ�������		
 **								 (2)OPA_ADJ_SEL_P		:������������������	
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_EnableAdjustMode(OP_Type *opa, uint32_t AdjustTarget);

/*****************************************************************************
 ** \brief	OPA_DisableAdjustMode
 **			 �ر��˷ŵ���ģʽ
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  none
 ** \note   
 *****************************************************************************/
void OPA_DisableAdjustMode(OP_Type *opa);

/*****************************************************************************
 ** \brief	OPA_EnableConfigAdjust
 **			 �����˷�Config����
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  none
 ** \note    ʹ��Config����ֵ
 *****************************************************************************/
void OPA_EnableConfigAdjust(OP_Type *opa);

/*****************************************************************************
 ** \brief	OPA_EnableOPADJAdjust
 **			 �����˷�OPADJ����
 ** \param [in] opa :OPA0 ��OPA1
 **				AdjustValue: 0x00 ~ 0x1f
 ** \return  none
 ** \note    ʹ��OPnADJ�Ĵ����е�OPnADJ<4:0>
 *****************************************************************************/
void OPA_EnableOPADJAdjust(OP_Type *opa, uint32_t AdjustValue);

/*****************************************************************************
 ** \brief	OPA_GetAutoAdjustResult
 **			 ��ȡ�˷ŵ���ģʽ���
 ** \param [in] opa :OPA0 ��OPA1
 ** \return  Result
 ** \note    
 *****************************************************************************/
uint32_t  OPA_GetAutoAdjustResult(OP_Type *opa);



#ifdef __cplusplus
}
#endif

#endif /* __OPA_H_ */

