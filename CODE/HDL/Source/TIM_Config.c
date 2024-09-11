
/*----------------------------------include-----------------------------------*/
#include "TIM_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void TMR1_Period_Count_Config(void)
{
	/*
	(1)设置Timer1 的时钟
	*/
	SYS_EnablePeripheralClk(SYS_CLK_TIMER01_MSK);			/*打开Timer0/1的时钟*/
	
	TMR01_SEL_CLK(TMR_CLK_SEL_HSI);			/*时钟源选择HSI*/
	TMR_ConfigClk(TIMER1,TMR_CLK_DIV_1);		/*Timer1设置时钟分频为 1分频*/
	/*
	(2)设置Timer1 运行模式
	*/	
	TMR_ConfigRunMode(TIMER1,TMR_COUNT_PERIOD_MODE, TMR_BIT_16_MODE);		/*设置Timer1为16位周期计数模式*/
	TMR_DisableOneShotMode(TIMER1);										/*关闭单次模式*/
	/*
	(3)设置Timer1 运行周期
	*/		
	TMR_SetPeriod(TIMER1,48000);				/* 48000*Fclk = 1000us*/
	/*
	(4)设置Timer1 中断
	*/	
	TMR_EnableOverflowInt(TIMER1);
	NVIC_EnableIRQ(TIMER1_IRQn);	
	/*
	(5)设置Timer1 中断优先级
	*/	
	NVIC_SetPriority(TIMER1_IRQn,3);	
	/*
	(5)开启Timer1
	*/	
	TMR_Start(TIMER1);			
}

void TIMER1_IRQHandler_Function(void)
{
    //hall 每次换相计数
    //计算速度，清零计数
    //更新速度

    //定时采集母线电压、母线电流、温度
}




/*------------------------------------test------------------------------------*/
