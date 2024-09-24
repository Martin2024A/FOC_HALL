
/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/
/*ͳһ�������������ṹ������*/
/*ͳһע��*/
/*ͳһ������󡢻ص�����*/
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

int  main(void)
{
	System_Init();    /*ϵͳ��ʼ��*/
	SoftwareInit();    /*�����ʼ��*/
	HardwareInit();    /*Ӳ����ʼ��*/
	EPWM_ConfigChannelSymDuty(EPWM0, 100);	
	while(1)
	{

	}	
}


void SoftwareInit(void)
{


}

void HardwareInit(void)
{
	ADC_Init();		
	// CCP_Init();
	EPWM_Init();
	// TIMER1_Init();		//��ʱ�ж�
	UART_Init();
	NVIC_Init();
}


void NVIC_Init(void)
{
	/*Hall*/
    NVIC_SetPriority(CCP_IRQn,0);		/*���ȼ�0~3�� 0��ߡ�3���*/		
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


















