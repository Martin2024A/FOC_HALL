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
/** \file isr.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms32m55xx.h"
#include "Motor_control.h"
#include "TIM_Config.h"
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

volatile uint32_t  CaptureTime = 0;				/*捕获的时间*/
volatile uint32_t  CaptureValue1 = 0;			/*第一次捕获的值*/
volatile uint32_t  CaptureValue2 = 0;			/*第二次捕获的值*/
volatile uint32_t  CaptureCount =0;
volatile uint32_t  OverFlowFlag =0;
/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/
     
/****************************************************************************
 ** \brief	NMI_Handler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void NMI_Handler(void)
{
	
}
/****************************************************************************
 ** \brief	HardFault_Handler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void HardFault_Handler(void)
{
	
}

/****************************************************************************
 ** \brief	SVC_Handler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void SVC_Handler(void)
{
	
}

/****************************************************************************
 ** \brief	PendSV_Handler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void PendSV_Handler(void)
{
	
}
/****************************************************************************
 ** \brief	SysTick_Handler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void SysTick_Handler(void)
{
	
}
           
/****************************************************************************
 ** \brief	GPIO0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void GPIO0_IRQHandler(void)
{

}

/****************************************************************************
 ** \brief	GPIO1_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
// void GPIO1_IRQHandler(void)
// {

	
// }
/****************************************************************************
 ** \brief	GPIO2_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void GPIO2_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	GPIO3_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void GPIO3_IRQHandler(void)
{

    //MC_SensorMode_HallChange(); 

	// if(GPIO_GetIntFlag(GPIO3,GPIO_PIN_1))
	// {
	// 	GPIO_ClearIntFlag(GPIO3,GPIO_PIN_1);
	// }	
	// if(GPIO_GetIntFlag(GPIO3,GPIO_PIN_2))
	// {
	// 	GPIO_ClearIntFlag(GPIO3,GPIO_PIN_2);
	// }	
	// if(GPIO_GetIntFlag(GPIO3,GPIO_PIN_4))
	// {
	// 	GPIO_ClearIntFlag(GPIO3,GPIO_PIN_4);
	// }	
}
/****************************************************************************
 ** \brief	GPIO4_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void GPIO4_IRQHandler(void)
{
	
}

/****************************************************************************
 ** \brief	CCP_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void CCP_IRQHandler(void)
{
	if(CCP_GetOverflowIntFlag(CCP1))
	{
		// CaptureCount = 0;						/*去掉在两次捕获中间出现计数溢出的情况*/
		
		CCP_ClearOverflowIntFlag(CCP1);
		
	}	
	if(CCP_GetCAPMode1IntFlag(CAP0))
	{		
	
		// if(CaptureCount ==0)
		// {
		// 	CaptureValue1 = CCP_GetCAPMode1Result(CAP0,0) ;	
		// }
		// else if(CaptureCount == 1)
		// {
		// 	CaptureValue2 = CCP_GetCAPMode1Result(CAP0,0) ;
		// 	CaptureTime = (CaptureValue1 - CaptureValue2)/0.75; /*捕获的时间（周期）= （第1次捕获值 - 第二次捕获值） / CCP模块的频率*/	
		// }
		// CaptureCount ++;		
	
		MC_SensorMode_HallChange();
		CCP_ClearCAPMode1IntFlag(CAP0);
	}
}
/****************************************************************************
 ** \brief	ADC0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void ADC0_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	WWDT_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void WWDT_IRQHandler(void)
{
		
}
/****************************************************************************
 ** \brief	EPWM_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/

/****************************************************************************
 ** \brief	ADC1_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/

void ADC1_IRQHandler(void)
{
	if(ADC1_GetChannelIntFlag(ADC1_CH_8))
	{
		ADC1_ClearChannelIntFlag(ADC1_CH_8);
	}			
}
/****************************************************************************
 ** \brief	ACMP_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void ACMP_IRQHandler(void)
{
	;
}
/****************************************************************************
 ** \brief	UART0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void UART0_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	UART1_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/

/****************************************************************************
 ** \brief	TIMER0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void TIMER0_IRQHandler(void)
{
		
}
/****************************************************************************
 ** \brief	TIMER1_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void TIMER1_IRQHandler(void)
{
	TIMER1_IRQHandler_Function();              
}


/****************************************************************************
 ** \brief	WDT_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void WDT_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	I2C0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void I2C0_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	SSP0_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void SSP0_IRQHandler(void)
{
	
}
/****************************************************************************
 ** \brief	SYS_CHK_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/
void SYS_CHK_IRQHandler(void)
{	

}



