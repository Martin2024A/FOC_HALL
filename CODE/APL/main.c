
/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/
/*统一函数、变量、结构体命名*/
/*统一注释*/
/*统一面向对象、回调函数*/
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

int  main(void)
{
	System_Init();    /*系统初始化*/
	SoftwareInit();    /*软件初始化*/
	HardwareInit();    /*硬件初始化*/
	while(1)
	{

	}	
}


void SoftwareInit(void)
{


}

void HardwareInit(void)
{
	// ADC_Init();		
	// CCP_Init();
	EPWM_Init();
	// TIMER1_Init();		//定时中断
	UART_Init();
	NVIC_Init();
}


void NVIC_Init(void)
{
	/*Hall*/
    NVIC_SetPriority(CCP_IRQn,0);		/*优先级0~3， 0最高、3最低*/		
    NVIC_EnableIRQ(CCP_IRQn);
	/*UART1*/
	NVIC_SetPriority(UART1_IRQn,3); 
    NVIC_EnableIRQ(UART1_IRQn); 
	/*ADC1*/
	NVIC_EnableIRQ(ADC1_IRQn);         
	NVIC_SetPriority(ADC1_IRQn,0);		
	/*EPWM*/
	NVIC_EnableIRQ(EPWM_IRQn);
	NVIC_SetPriority(EPWM_IRQn,3);	
	/*TIM1*/
	NVIC_EnableIRQ(TIMER1_IRQn);	
	NVIC_SetPriority(TIMER1_IRQn,3);				
}
/*------------------------------------test------------------------------------*/


















