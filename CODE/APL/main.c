
/*----------------------------------include-----------------------------------*/
#include "main.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
uint32_t ADCValue = 0;

/*-------------------------------------os-------------------------------------*/
/*

*/
/*----------------------------------function----------------------------------*/
int main(void)
{		
	SystemConfig();
	// SoftwareInit();
	HardwareInit();
	NVIC_Init();
	EPWM_Stop((EPWM_CH_0_MSK | EPWM_CH_1_MSK |
	 EPWM_CH_2_MSK | EPWM_CH_3_MSK |
	 EPWM_CH_4_MSK | EPWM_CH_5_MSK));

	while(1)
	{
		// FOC_Model();
		UartData_Processing();
	}	
}

void SystemConfig(void)
{
	SYS_DisableIOCFGProtect();			/*关闭IOCONFIG写保护*/
	SYS_DisableGPIO0Protect();			/*关闭GPIO0的相关寄存器写保护*/
	SYS_DisableGPIO1Protect();			/*关闭GPIO1的相关寄存器写保护*/
	SYS_DisableGPIO2Protect();			/*关闭GPIO2的相关寄存器写保护*/
	SYS_DisableGPIO3Protect();			/*关闭GPIO3的相关寄存器写保护*/
	SYS_DisableGPIO4Protect();			/*关闭GPIO4的相关寄存器写保护*/	
	
	SYS_ConfigHSI(SYS_CLK_HSI_48M);		/*设置内部高速时钟为48Mhz*/
	SYS_EnableHSI();					/*开启高速时钟*/
	SYS_ConfigAHBClock(SYS_CLK_SEL_HSI,SYS_CLK_DIV_1);	/*设置AHB时钟为高速时钟的1分频*/
	SYS_ConfigAPBClock(AHB_CLK_DIV_1);					/*设置APB时钟为AHB时钟的1分频*/
	SystemCoreClockUpdate();						/*刷新SystemCoreCLk、SystemAPBClock变量值*/
}

void SoftwareInit(void)
{
}

void HardwareInit(void)
{
//	GPIO_Init();
	// ADC_Init();		//母线电流
	// CCP_Init();		//Hall
	CCP_Capture_Mode1_Config();
	EPWM_Init();
	// MC_SensorMode_IOInit();
	// MC_SensorMode_Init();
	MC_SensorMode_Init();
	// TIM_Init();		//定时中断
	UART_Init();
}

void NVIC_Init(void)
{
//Hall GPIO 
    NVIC_SetPriority(GPIO3_IRQn,1); 
    NVIC_EnableIRQ(GPIO3_IRQn); 
//UART1
	NVIC_SetPriority(UART1_IRQn,3); 
    NVIC_EnableIRQ(UART1_IRQn); 
//ADC1
	NVIC_EnableIRQ(ADC1_IRQn);         //设置优先级
	NVIC_SetPriority(ADC1_IRQn,2);		//优先级0~3， 0最高、3最低	
}


void UartData_Processing(void)
{
//	static uint8_t showflag = 1;
//	int dec_temp=0;
   int speed_temp=0;
	char okCmd = 0;

	if(Serial_GetRxFlag() == 1)
	{
		if (U_ReceiveData[0] == 's')
		{
			if(U_ReceiveData[1] == '0')
			{
					printf("\n\rMotor_Ctrl.Motor_status = MOTOR_STOP\n\r");
					okCmd = 1;
					EPWM_Stop((EPWM_CH_0_MSK | EPWM_CH_1_MSK |
						 EPWM_CH_2_MSK | EPWM_CH_3_MSK |
						 EPWM_CH_4_MSK | EPWM_CH_5_MSK));
				}
						if(U_ReceiveData[1] == '1')
			{
						EPWM_Start((EPWM_CH_0_MSK | EPWM_CH_1_MSK |
						 EPWM_CH_2_MSK | EPWM_CH_3_MSK |
						 EPWM_CH_4_MSK | EPWM_CH_5_MSK));

					printf("\n\rMotor_Ctrl.Motor_status = MOTOR_STARTUP\n\r");
					okCmd = 1;
				}
			}
		else if(U_ReceiveData[0] == 'v' || U_ReceiveData[0] == 'V')
		{
			if(U_ReceiveData[1] == ' ')
			{
				speed_temp = atoi((char const *)U_ReceiveData+2);
				if(speed_temp >= 0 && speed_temp <= 100)
				{
					Stat_Volt_q_d.qV_Component2 = speed_temp*250;

					printf("\n\r速度: %d\n\r", speed_temp);
					okCmd = 1;
				}
			}
		}
//		if(okCmd != 1)
//		{
//			printf("\n\r 输入有误，请重新输入...\n\r");
//			show_help();
//		}
		}


}


void EPWM_IRQHandler(void)
{
	if( EPWM_GetPeriodIntFlag(EPWM0))
	{
		FOC_Model();
		EPWM_ClearPeriodIntFlag(EPWM0);
	}	

}





/*------------------------------------test------------------------------------*/


















