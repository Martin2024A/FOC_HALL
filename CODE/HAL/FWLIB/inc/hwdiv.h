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
/** \file hwdiv.h
**
** History:
** 
*****************************************************************************/
#ifndef __HWDIV_H_
#define __HWDIV_H_

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
/*****************************************************************************
 ** \brief	HWDIV_DIV_IS_0
 **			�жϳ����Ƿ�Ϊ0
 ** \param [in] none
 ** \return  1������Ϊ0  0��������Ϊ0
 ** \note	 
*****************************************************************************/
#define	 HWDIV_DIV_IS_0()	(((HWDIV->CON & HDIV_CON_DIVBY0_Msk)?1:0))
/*****************************************************************************
 ** \brief	HWDIV_IS_IDLE
 **			�жϳ������ǿ���
 ** \param [in] none
 ** \return  1������  0����������
 ** \note	 
*****************************************************************************/
#define	 HWDIV_IS_IDLE()	(((HWDIV->CON & HDIV_CON_READY_Msk)?1:0))

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
 ** \brief	HWDIV_Div
 **			ʵ�� "/" (ȡ��)
 ** \param [in] x:������
 **				y:����
 ** \return  none
 ** \note	 
*****************************************************************************/
int32_t HWDIV_Div(int32_t x, int32_t y);
	  
/*****************************************************************************
 ** \brief	HWDIV_Mod
 **			ʵ�� "%" (ȡ��)
 ** \param [in] x:������
 **				y:����
 ** \return  none
 ** \note	 
*****************************************************************************/
int32_t HWDIV_Mod(int32_t x, int32_t y);

/*****************************************************************************
 ** \brief	HWDIV_EnableSingedMode
 **			ʹ���з��ų���������
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void HWDIV_EnableSingedMode(void);
/*****************************************************************************
 ** \brief	HWDIV_EnableUnsingedMode
 **			ʹ���޷��ų���������
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void HWDIV_EnableUnsingedMode(void);





#ifdef __cplusplus
}
#endif

#endif /* __HWDIV_H_*/

