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
/** \file pga.h
**
** History:
** 
*****************************************************************************/
#ifndef __PGA_H_
#define __PGA_H_

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
 **PGA	����ѡ��
-----------------------------------------------------------------------------*/
#define		PGA_GAIN_4			(0x00UL)					/*��������Ϊ4x*/
#define		PGA_GAIN_8			(0x01UL<<PGA_CON_GS_Pos)	/*��������Ϊ8x*/
#define		PGA_GAIN_10			(0x02UL<<PGA_CON_GS_Pos)	/*��������Ϊ10x*/
#define		PGA_GAIN_12			(0x03UL<<PGA_CON_GS_Pos)	/*��������Ϊ12x*/			
#define		PGA_GAIN_14			(0x04UL<<PGA_CON_GS_Pos)	/*��������Ϊ14x*/
#define		PGA_GAIN_16			(0x05UL<<PGA_CON_GS_Pos)	/*��������Ϊ16x*/	
#define		PGA_GAIN_32			(0x06UL<<PGA_CON_GS_Pos)	/*��������Ϊ32x*/
/*----------------------------------------------------------------------------
 **PGA	��������ӵض�ѡ��
-----------------------------------------------------------------------------*/
#define		PGA_R_GND			(0x00UL)					/*�ӵ��ڲ�GND*/
#define		PGA_R_PIN			(0x01UL<<PGA_CON_RGS_Pos)	/*�ӵ�AGND*/
			
/*----------------------------------------------------------------------------
 **PGA	����
-----------------------------------------------------------------------------*/
#define		PGA_POSSEL_P0		(0x00UL)					/*�ӵ�PGA P0*/
#define		PGA_POSSEL_P1		(0x01UL<<PGA_CON_PS_Pos)	/*�ӵ�PGA P1*/
#define		PGA_POSSEL_P2		(0x02UL<<PGA_CON_PS_Pos)	/*�ӵ�PGA P2*/
#define		PGA_POSSEL_P3		(0x03UL<<PGA_CON_PS_Pos)	/*�ӵ�PGA P3*/

/*----------------------------------------------------------------------------
 **PGA	�����
-----------------------------------------------------------------------------*/
#define		PGA_OUTSEL_O		(0x01UL<<PGA_CON_OS_Pos)	


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
 ** \brief	 PGA_ConfigPositive
 **			 ����PGA��������
 ** \param [in] pga :PGA0 ��PGA1
 **				Positive:	(1)PGA_POSSEL_P0
 **							(2)PGA_POSSEL_P1
 ** \return  none	
 ** \note    
 *****************************************************************************/
void PGA_ConfigPositive(PGA_Type *pga, uint32_t Positive);

/*****************************************************************************
 ** \brief	 OPA_ConfigGain
 **			 ����PGA����
 ** \param [in] pga :PGA0 ��PGA1
 **				Gain:  (1)PGA_GAIN_4		
 **					   (2)PGA_GAIN_8 
 **					   (3)PGA_GAIN_10 
 **					   (4)PGA_GAIN_12 
 **					   (5)PGA_GAIN_14 
 **					   (6)PGA_GAIN_16 
 **					   (6)PGA_GAIN_32 
 ** \return  none
 ** \note    
 *****************************************************************************/
void PGA_ConfigGain(PGA_Type *pga, uint32_t Gain);

/*****************************************************************************
 ** \brief	 PGA_ConfigResistorGnd
 **			 ����PGA��������ӵض�
 ** \param [in] pga :PGA0 ��PGA1
 **				GndMode:	(1)PGA_R_GND
 **							(2)PGA_R_PIN
 ** \return  none	
 ** \note    
 *****************************************************************************/
void PGA_ConfigResistorGnd(PGA_Type *pga, uint32_t GndMode);

/*****************************************************************************
 ** \brief	 PGA_ConfigOutput
 **			 ����PGA�����
 ** \param [in] pga :PGA0 ��PGA1
 **				Output:	(1)PGA_OUTSEL_O
 ** \return  none	
 ** \note    
 *****************************************************************************/
void PGA_ConfigOutput(PGA_Type *pga, uint32_t Output);

/*****************************************************************************
 ** \brief	 PGA_Start
 **			 ����PGA
 ** \param [in] pga :PGA0 ��PGA1
 ** \return  none	
 ** \note    
 *****************************************************************************/
void PGA_Start(PGA_Type *pga);

/*****************************************************************************
 ** \brief	 PGA_Stop
 **			 �ر�PGA
 ** \param [in] pga :PGA0 ��PGA1
 ** \return  none	
 ** \note    
 *****************************************************************************/
void PGA_Stop(PGA_Type *pga);


#ifdef __cplusplus
}
#endif

#endif /* ____ */

