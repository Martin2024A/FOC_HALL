
/*----------------------------------include-----------------------------------*/
#include "main.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
/*-----------------------------------------------------------------------------
Function Name :	void main(void)
Description   :	主函数主要功能是初始化，包括:
				系统初始化--系统时钟配置，看门狗配置
				软件初始化--初始化所有定义的变量
				硬件初始化--初始化硬件设备配置
				主循环扫描--看门狗喂狗，电机控制状态扫描，调试测试函数
Input         :	无
Output        :	无
-------------------------------------------------------------------------------*/
int  main(void)
{		
	System_Init();    /*系统初始化*/
	SoftwareInit();    /*软件初始化*/
	HardwareInit();    /*硬件初始化*/

	while(1)
	{
		// Motor_Control();
		// UartData_Processing();
	}	
}



/*-------------------------------------------------------------------------------
Function Name :	void SoftwareInit(void)
Description   :	软件初始化，初始化所有定义变量
Input         :	无
Output		  :	无
--------------------------------------------------------------------------------*/
void SoftwareInit(void)
{


}

/*--------------------------------------------------------------------------------
Function Name :	void HardwareInit(void)
Description   :	硬件初始化，初始化需要使用的硬件设备配置
Input         :	无
Output		  :	无
--------------------------------------------------------------------------------*/
void HardwareInit(void)
{
	// ADC_Init();		
	CCP_Init();
	// EPWM_Init();
	// TIMER1_Init();		//定时中断
	UART_Init();
}


/*--------------------------------------------------------------------------------
Function Name :	void NVIC_Init(void)
Description   :	中断初始化，优先级设置
Input         :	无
Output		  :	无
--------------------------------------------------------------------------------*/
void NVIC_Init(void)
{
	/*修改，FOC高频、中频速度环、低频霍尔，设置优先级*/
//Hall 
    NVIC_SetPriority(CCP_IRQn,0);		/*优先级0~3， 0最高、3最低*/		
    NVIC_EnableIRQ(CCP_IRQn);
//UART1
	NVIC_SetPriority(UART1_IRQn,3); 
    NVIC_EnableIRQ(UART1_IRQn); 
//ADC1
	NVIC_EnableIRQ(ADC1_IRQn);         //设置优先级
	NVIC_SetPriority(ADC1_IRQn,2);		//优先级0~3， 0最高、3最低	
}
/*------------------------------------test------------------------------------*/


















