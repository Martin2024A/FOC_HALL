
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
	(1)����Timer1 ��ʱ��
	*/
	SYS_EnablePeripheralClk(SYS_CLK_TIMER01_MSK);			/*��Timer0/1��ʱ��*/
	
	TMR01_SEL_CLK(TMR_CLK_SEL_HSI);			/*ʱ��Դѡ��HSI*/
	TMR_ConfigClk(TIMER1,TMR_CLK_DIV_1);		/*Timer1����ʱ�ӷ�ƵΪ 1��Ƶ*/
	/*
	(2)����Timer1 ����ģʽ
	*/	
	TMR_ConfigRunMode(TIMER1,TMR_COUNT_PERIOD_MODE, TMR_BIT_16_MODE);		/*����Timer1Ϊ16λ���ڼ���ģʽ*/
	TMR_DisableOneShotMode(TIMER1);										/*�رյ���ģʽ*/
	/*
	(3)����Timer1 ��������
	*/		
	TMR_SetPeriod(TIMER1,48000);				/* 48000*Fclk = 1000us*/
	/*
	(4)����Timer1 �ж�
	*/	
	TMR_EnableOverflowInt(TIMER1);
	NVIC_EnableIRQ(TIMER1_IRQn);	
	/*
	(5)����Timer1 �ж����ȼ�
	*/	
	NVIC_SetPriority(TIMER1_IRQn,3);	
	/*
	(5)����Timer1
	*/	
	TMR_Start(TIMER1);			
}

void TIMER1_IRQHandler_Function(void)
{
    //hall ÿ�λ������
    //�����ٶȣ��������
    //�����ٶ�

    //��ʱ�ɼ�ĸ�ߵ�ѹ��ĸ�ߵ������¶�
}




/*------------------------------------test------------------------------------*/
