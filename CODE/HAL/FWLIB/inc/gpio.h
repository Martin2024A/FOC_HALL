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
/** \file gpio.h
**
** History:
** 
*****************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

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
 **GPIO PORT & PIN
-----------------------------------------------------------------------------*/
#define		GPIO_PIN_NUM_MAX	(0x08UL)
#define 	GPIO_PIN_0_MSK		(0x01UL)		/*GPIO Pin 0 mask*/
#define 	GPIO_PIN_1_MSK		(0x02UL)		/*GPIO Pin 1 mask*/
#define 	GPIO_PIN_2_MSK		(0x04UL)		/*GPIO Pin 2 mask*/
#define 	GPIO_PIN_3_MSK		(0x08UL)		/*GPIO Pin 3 mask*/		
#define 	GPIO_PIN_4_MSK		(0x10UL)		/*GPIO Pin 4 mask*/
#define 	GPIO_PIN_5_MSK		(0x20UL)		/*GPIO Pin 5 mask*/
#define 	GPIO_PIN_6_MSK		(0x40UL)		/*GPIO Pin 6 mask*/
#define 	GPIO_PIN_7_MSK		(0x80UL)		/*GPIO Pin 7 mask*/

#define 	GPIO_PIN_0			(0x00UL)		/*GPIO Pin 0 Num*/
#define 	GPIO_PIN_1			(0x01UL)		/*GPIO Pin 1 Num*/
#define 	GPIO_PIN_2			(0x02UL)		/*GPIO Pin 2 Num*/
#define 	GPIO_PIN_3			(0x03UL)		/*GPIO Pin 3 Num*/
#define 	GPIO_PIN_4			(0x04UL)		/*GPIO Pin 4 Num*/		
#define 	GPIO_PIN_5			(0x05UL)		/*GPIO Pin 5 Num*/
#define 	GPIO_PIN_6			(0x06UL)		/*GPIO Pin 6 Num*/
#define 	GPIO_PIN_7			(0x07UL)		/*GPIO Pin 7 Num*/

/*----------------------------------------------------------------------------
 **GPIO ģʽ 
-----------------------------------------------------------------------------*/
#define 	GPIO_MODE_INPUT						(0x00UL)		/*��ͨ����ģʽ*/
#define 	GPIO_MODE_OUTPUT					(0x01UL)		/*�������ģʽ*/
#define 	GPIO_MODE_OPEN_DRAIN_WITHOUT_PULL_UP		(0x02UL)		/*���������Ŀ�©���ģʽ*/
#define 	GPIO_MODE_INPUT_WITH_PULL_UP		(0x03UL)		/*��������ģʽ*/
#define		GPIO_MODE_INPUT_WITH_PULL_DOWN		(0x04UL)		/*��������ģʽ*/

/*----------------------------------------------------------------------------
 **GPIO �ж�ģʽ
-----------------------------------------------------------------------------*/
#define 	GPIO_INT_LEVEL_LOW			(0x00UL)			/*GPIO��ƽ������ʽ�еĵ͵�ƽ������ʽ*/
#define 	GPIO_INT_LEVEL_HIGH			(0x01UL)			/*GPIO��ƽ������ʽ�еĸߵ�ƽ������ʽ*/
#define 	GPIO_INT_EDGE_FALLING		(0x02UL)			/*GPIO���ش�����ʽ�е��½��ش�����ʽ*/
#define 	GPIO_INT_EDGE_RISING		(0x03UL)			/*GPIO���ش�����ʽ�е������ش�����ʽ*/
#define 	GPIO_INT_EDGE_BOTH			(0x04UL)			/*GPIO���ش�����ʽ�е��������½��ش�����ʽ*/
/*----------------------------------------------------------------------------
 **GPIO �˲�ʱ��
-----------------------------------------------------------------------------*/
#define 	GPIO_FILCLK_DIV_1			(0x0UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/1*/
#define 	GPIO_FILCLK_DIV_2			(0x1UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/2*/
#define 	GPIO_FILCLK_DIV_4			(0x2UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/4*/
#define 	GPIO_FILCLK_DIV_6			(0x3UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/6*/
#define 	GPIO_FILCLK_DIV_8			(0x4UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/8*/
#define 	GPIO_FILCLK_DIV_10			(0x5UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/10*/
#define 	GPIO_FILCLK_DIV_12			(0x6UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/12*/
#define 	GPIO_FILCLK_DIV_14			(0x7UL<<GPIO_DIDB_DBCK_Pos)		/*Filter Clk = HCLK/14*/



/*****************************************************************************
 ** \brief	GPIO_CONFIG_IO_MODE
 **			����IO��ģʽ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 **				IOMode ��(1)GPIO_MODE_INPUT
 **						 (2)GPIO_MODE_OUTPUT
 **						 (3)GPIO_MODE_OPEN_DRAIN_WITHOUT_PULL_UP
 **						 (4)GPIO_MODE_INPUT_WITH_PULL_UP
 **						 (5)GPIO_MODE_INPUT_WITH_PULL_DOWN
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_CONFIG_IO_MODE(port,PinNum ,IOMode)  do{\
														port->GPIO0PMS &= ~(GPIO_PMS_PMS0_Msk <<(PinNum*4));\
														port->GPIO0PMS |= (IOMode <<(PinNum*4));\
													 }while(0)
/*****************************************************************************
 ** \brief	GPIO_ENABLE_DO_SHIELD
 **			����GPIO�������д����
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_ENABLE_DO_SHIELD(port,PinMask)  do{\
													port->GPIO0DOM =  PinMask;\
												}while(0)													 
/*****************************************************************************
 ** \brief	GPIO_DISABLE_DO_SHIELD
 **			�ر�GPIO�������д����
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_DISABLE_DO_SHIELD(port,PinMask)  do{\
													port->GPIO0DOM = ~(PinMask);\
												}while(0)														 

/*****************************************************************************
 ** \brief	 GPIO_DISABLE_LOW_CURRENT
 **			 �ر�GPIO��С����ģʽ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_DISABLE_LOW_CURRENT(port,PinMask)  do{\
													port->GPIO0DR &= ~(PinMask);\
												}while(0)	
/*****************************************************************************
 ** \brief	 GPIO_ENABLE_LOW_CURRENT
 **			 ����GPIO��С����ģʽ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_ENABLE_LOW_CURRENT(port,PinMask)  do{\
													port->GPIO0DR |= (PinMask);\
												}while(0)

/*****************************************************************************
 ** \brief	 GPIO_DISABLE_SLOW_SLOPE
 **			 �ر�GPIO����б��
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_DISABLE_SLOW_SLOPE(port,PinMask)  do{\
													port->GPIO0SR &= ~(PinMask);\
												}while(0)	
/*****************************************************************************
 ** \brief	 GPIO_ENABLE_SLOW_SLOPE
 **			 ����GPIO����б��
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_ENABLE_SLOW_SLOPE(port,PinMask)  do{\
													port->GPIO0SR |= (PinMask);\
												}while(0)	

/*****************************************************************************
 ** \brief	 GPIO_SET_PIN
 **			 �ܽ���λ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_SET_PIN(port,PinMask)  do{\
											port->GPIO0DOSET = (PinMask);\
										}while(0)	
/*****************************************************************************
 ** \brief	 GPIO_RESET_PIN
 **			 ����/��λ�ܽ�
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   GPIO_RESET_PIN(port,PinMask)  do{\
											port->GPIO0DOCLR = (PinMask);\
										   }while(0)	

/*****************************************************************************
 ** \brief	 GPIO_GET_RIS_FLAG
 **			 ��ȡIO�ж�Դ��־
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 ** \return 0:�����жϣ� 1��δ�����ж�
 ** \note	 
*****************************************************************************/
#define   GPIO_GET_RIS_FLAG(port,PinNum)  (((port->GPIO0RIS & (0x1UL<<PinNum))? 1:0))

												
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
 ** \brief	 GPIO_ConfigRunMode
 **			 ����IO������ģʽ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 **				Mode:	 (1)GPIO_MODE_INPUT
 **						 (2)GPIO_MODE_OUTPUT
 **						 (3)GPIO_MODE_OPEN_DRAIN_WITHOUT_PULL_UP
 **						 (4)GPIO_MODE_INPUT_WITH_PULL_UP
 **						 (5)GPIO_MODE_INPUT_WITH_PULL_DOWN
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_ConfigRunMode(GPIO0_Type *port, uint32_t PinMask, uint32_t Mode);
/*****************************************************************************
 ** \brief	 GPIO_EnableFilter
 **			 ����IO�������˲�
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 **				Fclk:	 (1)GPIO_FILCLK_DIV_1
 **						 (2)GPIO_FILCLK_DIV_2
 **						 (3)GPIO_FILCLK_DIV_4
 **						 (4)GPIO_FILCLK_DIV_6
 **						 (5)GPIO_FILCLK_DIV_8
 **						 (6)GPIO_FILCLK_DIV_10
 **						 (7)GPIO_FILCLK_DIV_12
 **						 (8)GPIO_FILCLK_DIV_14
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_EnableFilter(GPIO0_Type *port, uint32_t PinMask, uint32_t Fclk);
/*****************************************************************************
 ** \brief	 GPIO_DisableFilter
 **			 �ر�IO�������˲�
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_DisableFilter(GPIO0_Type *port, uint32_t PinMask);

/*****************************************************************************
 ** \brief	 GPIO_EnableInt
 **			 ����IO���ж�
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 **				Mode: (1)GPIO_INT_LEVEL_LOW
 **					  (2)GPIO_INT_LEVEL_HIGH
 **					  (3)GPIO_INT_EDGE_FALLING 
 **					  (4)GPIO_INT_EDGE_RISING
 **					  (5)GPIO_INT_EDGE_BOTH
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_EnableInt(GPIO0_Type *port, uint32_t PinMask, uint32_t IntMode);

/*****************************************************************************
 ** \brief	 GPIO_DisableInt
 **			 �ر�IO���ж�
 ** \param [in]port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **		       PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_DisableInt(GPIO0_Type *port, uint32_t Pin);

/*****************************************************************************
 ** \brief	 GPIO_GetIntFlag
 **			 ��ȡIO����ʹ���жϱ�־λ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 ** \return  0��δ�����ж� 1���ж���ʹ�ܲ������ж�
 ** \note	
*****************************************************************************/
uint32_t GPIO_GetIntFlag(GPIO0_Type *port, uint32_t PinNum);

/*****************************************************************************
 ** \brief	 GPIO_ClearIntFlag
 **			 ���IO���жϱ�־λ
 ** \param [in] port : GPIO0��GPIO1 ��GPIO2��GPIO3��GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_ClearIntFlag(GPIO0_Type *port, uint32_t PinNum);



#ifdef __cplusplus
}
#endif
#endif /* __GPIO_H__ */

