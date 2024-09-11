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
/** \file gpio.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "gpio.h"
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
 ** \brief	 GPIO_ConfigRunMode
 **			 配置IO口运行模式
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 **				Mode:	 (1)GPIO_MODE_INPUT
 **						 (2)GPIO_MODE_OUTPUT
 **						 (3)GPIO_MODE_OPEN_DRAIN_WITHOUT_PULL_UP
 **						 (4)GPIO_MODE_INPUT_WITH_PULL_UP
 **						 (5)GPIO_MODE_INPUT_WITH_PULL_DOWN
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_ConfigRunMode(GPIO0_Type *port, uint32_t PinMask, uint32_t Mode)
{
	uint32_t Num;
	uint32_t Size =4;
	for(Num =0; Num <GPIO_PIN_NUM_MAX; Num++)
	{
		if(PinMask & (0x1 <<Num))
		{
			port->GPIO0PMS &= ~(0x3 <<(Num*Size));
			port->GPIO0PMS |= (Mode <<(Num*Size));
		}
	}
}
/*****************************************************************************
 ** \brief	 GPIO_EnableInt
 **			 开启IO口中断
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 **				Mode: (1)GPIO_INT_LEVEL_LOW
 **					  (2)GPIO_INT_LEVEL_HIGH
 **					  (3)GPIO_INT_EDGE_FALLING 
 **					  (4)GPIO_INT_EDGE_RISING
 **					  (5)GPIO_INT_EDGE_BOTH
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_EnableInt(GPIO0_Type *port, uint32_t PinMask, uint32_t IntMode)
{
	switch(IntMode)
	{
		case GPIO_INT_LEVEL_LOW:
			port->GPIO0ITYPE |= PinMask;
			port->GPIO0IVAL  &= ~(PinMask);
			break;
		case GPIO_INT_LEVEL_HIGH:
			port->GPIO0ITYPE |= PinMask;
			port->GPIO0IVAL  |= PinMask;	
			break;
		case GPIO_INT_EDGE_FALLING:
			port->GPIO0ITYPE &= ~(PinMask);
			port->GPIO0IVAL  &= ~(PinMask);
			port->GPIO0IANY  &= ~(PinMask);
			break;
		case GPIO_INT_EDGE_RISING:
			port->GPIO0ITYPE &= ~(PinMask);
			port->GPIO0IVAL  |= PinMask;
			port->GPIO0IANY  &= ~(PinMask);
			break;
		case GPIO_INT_EDGE_BOTH:
			port->GPIO0ITYPE &= ~(PinMask);
			port->GPIO0IANY  |= PinMask;
			break;
		default:
			break;
	}
	port->GPIO0IMSC  |= PinMask;
}

/*****************************************************************************
 ** \brief	 GPIO_DisableInt
 **			 关闭IO口中断
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_DisableInt(GPIO0_Type *port, uint32_t PinMask)
{
	port->GPIO0IMSC  &= ~(PinMask);
}

/*****************************************************************************
 ** \brief	 GPIO_GetIntFlag
 **			 获取IO口已使能中断标志位
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 ** \return  0：未产生中断 1：中断已使能并产生中断
 ** \note	
*****************************************************************************/
uint32_t GPIO_GetIntFlag(GPIO0_Type *port, uint32_t PinNum)
{
	return((port->GPIO0MIS &(0x1<< PinNum))? 1:0);
}

/*****************************************************************************
 ** \brief	 GPIO_ClearIntFlag
 **			 清除IO口中断标志位
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinNum: GPIO_PIN_0 ~ GPIO_PIN_7
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_ClearIntFlag(GPIO0_Type *port, uint32_t PinNum)
{
	port->GPIO0ICLR |= (0x1<< PinNum);
}

/*****************************************************************************
 ** \brief	 GPIO_EnableFilter
 **			 开启IO口输入滤波
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
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
void GPIO_EnableFilter(GPIO0_Type *port, uint32_t PinMask, uint32_t Fclk)
{
	port->GPIO0DIDB &= ~(GPIO_DIDB_DBCK_Msk);
	port->GPIO0DIDB |=(PinMask | Fclk);	
}
/*****************************************************************************
 ** \brief	 GPIO_DisableFilter
 **			 关闭IO口输入滤波
 ** \param [in] port : GPIO0、GPIO1 、GPIO2、GPIO3、GPIO4
 **				PinMask: GPIO_PIN_0_MSK ~ GPIO_PIN_7_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void GPIO_DisableFilter(GPIO0_Type *port, uint32_t PinMask)
{
	port->GPIO0DIDB &= ~(PinMask);
}
