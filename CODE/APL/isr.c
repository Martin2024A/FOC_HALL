/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

volatile uint32_t  CaptureTime = 0;				/*�����ʱ��*/
volatile uint32_t  CaptureValue1 = 0;			/*��һ�β����ֵ*/
volatile uint32_t  CaptureValue2 = 0;			/*�ڶ��β����ֵ*/
volatile uint32_t  CaptureCount =0;
volatile uint32_t  OverFlowFlag =0;
volatile uint8_t  ADCFlag =0;
volatile uint32_t  CMPD =0;
volatile uint32_t  ADC8 =0;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
   
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
	uint8_t halldata;
	if(CCP_GetOverflowIntFlag(CCP1))
	{
		// CaptureCount = 0;						/*ȥ�������β����м���ּ�����������*/
		
		CCP_ClearOverflowIntFlag(CCP1);
		
	}	
	if(CCP_GetCAPMode1IntFlag(CAP0)||CCP_GetCAPMode1IntFlag(CAP1)||CCP_GetCAPMode1IntFlag(CAP2))
	{		
	
		// if(CaptureCount ==0)
		// {
		// 	CaptureValue1 = CCP_GetCAPMode1Result(CAP0,0) ;	
		// }
		// else if(CaptureCount == 1)
		// {
		// 	CaptureValue2 = CCP_GetCAPMode1Result(CAP0,0) ;
		// 	CaptureTime = (CaptureValue1 - CaptureValue2)/0.75; /*�����ʱ�䣨���ڣ�= ����1�β���ֵ - �ڶ��β���ֵ�� / CCPģ���Ƶ��*/	
		// }
		// CaptureCount ++;		
	
		// halldata = get_hallValue();
		// printf(" %d \n\r",halldata);
		CCP_ClearCAPMode1IntFlag(CAP0);
		CCP_ClearCAPMode1IntFlag(CAP1);
		CCP_ClearCAPMode1IntFlag(CAP2);
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
void EPWM_IRQHandler(void)
{
	if( EPWM_GetPeriodIntFlag(EPWM0))
	{
//		FOC_Model();
		EPWM_ClearPeriodIntFlag(EPWM0);
	}	
}

/****************************************************************************
 ** \brief	ADC1_IRQHandler
 **
 ** \param [in]  none   
 ** \return none
 ** \note
****************************************************************************/

void ADC1_IRQHandler(void)
{
	if(ADC1_GetChannelIntFlag(ADC1_CH_30))
	{
		if(ADCFlag == 0)
		{

			EPWM_ConfigCompareTriger(EPWM_CMPTG_0,EPWM_CMPTG_FALLING,EPWM_CMPTG_EPWM2,100);
			ADCFlag = 1;
		}
		if(ADCFlag == 1)
		{

		}
		ADC1_ClearChannelIntFlag(ADC1_CH_30);
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
//	TIMER1_IRQHandler_Function();              
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



