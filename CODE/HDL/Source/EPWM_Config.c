/*----------------------------------include-----------------------------------*/
#include "EPWM_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void EPWM_Init(void)
{
	/*
	(1)设置EPWM运行模式
	*/
	EPWM_ConfigRunMode(  EPWM_COUNT_UP_DOWN 	| 		
						 EPWM_OCU_SYMMETRIC 	|			/*对称模式*/
						 EPWM_WFG_INDEPENDENT   |			/*独立，非互补同步*/
						 EPWM_OC_INDEPENDENT);				/*独立，非分组*/
	
	/*
	(2)设置EPWM时钟周期与死区
	*/
	SYS_EnablePeripheralClk(SYS_CLK_EPWM_MSK);				/*开启EPWM时钟*/
	
	EPWM_ConfigChannelClk( EPWM0, EPWM_CLK_DIV_1);			/*设置EPWM0时钟为APB时钟的1分频48M*/
	EPWM_ConfigChannelClk( EPWM2, EPWM_CLK_DIV_1);			/*设置EPWM2时钟为APB时钟的1分频*/
	EPWM_ConfigChannelClk( EPWM4, EPWM_CLK_DIV_1);			/*设置EPWM4时钟为APB时钟的1分频*/
	EPWM_ConfigChannelClk( EPWM1, EPWM_CLK_DIV_1);			
	EPWM_ConfigChannelClk( EPWM3, EPWM_CLK_DIV_1);			
	EPWM_ConfigChannelClk( EPWM5, EPWM_CLK_DIV_1);			
	
	EPWM_ConfigChannelPeriod(EPWM0,  4800);					/*EPWM0通道的周期 = 2*4800/Fepwm = 200us*/
	EPWM_ConfigChannelPeriod(EPWM2,  4800);			
	EPWM_ConfigChannelPeriod(EPWM4,  4800);	
	EPWM_ConfigChannelPeriod(EPWM1,  4800);					/*EPWM0通道的周期 = 2*4800/Fepwm = 200us*/
	EPWM_ConfigChannelPeriod(EPWM3,  4800);			
	EPWM_ConfigChannelPeriod(EPWM5,  4800);						

	EPWM_ConfigChannelSymDuty(EPWM0, 0);					/*EPWM0通道的占空比 = 25%*/
	EPWM_ConfigChannelSymDuty(EPWM2, 0);					/*EPWM2通道的占空比 = 50%*/	
	EPWM_ConfigChannelSymDuty(EPWM4, 0);					/*EPWM4通道的占空比 = 75%*/	
	EPWM_ConfigChannelSymDuty(EPWM1, 0);					/*EPWM0通道的占空比 = 25%*/
	EPWM_ConfigChannelSymDuty(EPWM3, 0);					/*EPWM2通道的占空比 = 50%*/	
	EPWM_ConfigChannelSymDuty(EPWM5, 0);					/*EPWM4通道的占空比 = 75%*/	

	EPWM_DisableDeadZone(EPWM_CH_0_MSK | EPWM_CH_1_MSK |
						 EPWM_CH_2_MSK | EPWM_CH_3_MSK |
						 EPWM_CH_4_MSK | EPWM_CH_5_MSK);	/*关闭死区*/


	/*
	(3)设置EPWM反向输出
	*/
	EPWM_EnableReverseOutput( EPWM_CH_3_MSK | EPWM_CH_4_MSK | EPWM_CH_5_MSK );		/*开启反相输出*/

	/*
	(4)设置EPWM加载方式
	*/
	EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK | EPWM_CH_2_MSK | EPWM_CH_4_MSK| EPWM_CH_1_MSK | EPWM_CH_3_MSK| EPWM_CH_5_MSK);	/*设置为自动加载模式*/
	EPWM_ConfigLoadAndIntMode(EPWM0, EPWM_EACH_PERIOD_ZERO);			/*加载点设置为每个周期点和零点*/
	EPWM_ConfigLoadAndIntMode(EPWM2, EPWM_EACH_PERIOD_ZERO);
	EPWM_ConfigLoadAndIntMode(EPWM4, EPWM_EACH_PERIOD_ZERO);			
	EPWM_ConfigLoadAndIntMode(EPWM1, EPWM_EACH_PERIOD_ZERO);			
	EPWM_ConfigLoadAndIntMode(EPWM3, EPWM_EACH_PERIOD_ZERO);
	EPWM_ConfigLoadAndIntMode(EPWM5, EPWM_EACH_PERIOD_ZERO);			

	/*
	(5)设置EPWM刹车
	*/
    EPWM_AllBrakeDisable();

	/*(6)设置中断
	*/
	EPWM_EnablePeriodInt(EPWM_CH_0_MSK);								/*开启中断*/		
	
	
	/*
	(6)设置触发比较器
	*/	
	EPWM_ConfigCompareTriger(EPWM_CMPTG_0,EPWM_CMPTG_FALLING,EPWM_CMPTG_EPWM0,1000);
	
	
	/*
	(7)设置IO口输出
	*/	
    SYS_SET_IOCFG(IOP01CFG, SYS_IOCFG_P01_EPWM0); 
	SYS_SET_IOCFG(IOP04CFG, SYS_IOCFG_P04_EPWM1);
	SYS_SET_IOCFG(IOP05CFG, SYS_IOCFG_P05_EPWM2);

    SYS_SET_IOCFG(IOP06CFG,SYS_IOCFG_P06_EPWM3);	
    SYS_SET_IOCFG(IOP07CFG,SYS_IOCFG_P07_EPWM4);
    SYS_SET_IOCFG(IOP47CFG,SYS_IOCFG_P47_EPWM5);	
	
	
	EPWM_EnableOutput(EPWM_CH_0_MSK | EPWM_CH_1_MSK |
					  EPWM_CH_2_MSK | EPWM_CH_3_MSK |
					  EPWM_CH_4_MSK | EPWM_CH_5_MSK );

	/*
	(8)开启EPWM
	*/		
	EPWM_Start(EPWM_CH_0_MSK | EPWM_CH_2_MSK | EPWM_CH_4_MSK| EPWM_CH_1_MSK| EPWM_CH_3_MSK| EPWM_CH_5_MSK);
}

#ifdef DEBUG_REMAP
void EPWM_Init(void)
{
	/*
	(1)设置EPWM运行模式
	*/
	EPWM_ConfigRunMode(  EPWM_COUNT_UP_DOWN 	| 		
						 EPWM_OCU_ASYMMETRIC 	|			/*非对称模式*/
						 EPWM_WFG_COMPLEMENTARYK   |		/*互补*/
						 EPWM_OC_INDEPENDENT);				/*独立，非分组*/
	
	/*
	(2)设置EPWM时钟周期与死区
	*/
	SYS_EnablePeripheralClk(SYS_CLK_EPWM_MSK);				/*开启EPWM时钟*/
	
	EPWM_ConfigChannelClk( EPWM0, EPWM_CLK_DIV_1);			/*设置EPWM0时钟为APB时钟的1分频48M*/
	EPWM_ConfigChannelClk( EPWM2, EPWM_CLK_DIV_1);			/*设置EPWM2时钟为APB时钟的1分频*/
	EPWM_ConfigChannelClk( EPWM4, EPWM_CLK_DIV_1);			/*设置EPWM4时钟为APB时钟的1分频*/

	
	EPWM_ConfigChannelPeriod(EPWM0,  4800);					/*EPWM0通道的周期 = 2*4800/Fepwm = 200us*/
	EPWM_ConfigChannelPeriod(EPWM2,  4800);			
	EPWM_ConfigChannelPeriod(EPWM4,  4800);	
		
	EPWM_ConfigChannelAsymDuty(EPWM0, 0, 0);			/*非对称模式下EPWM0通道的占空比*/
	EPWM_ConfigChannelAsymDuty(EPWM2, 0, 0);
	EPWM_ConfigChannelAsymDuty(EPWM4, 0, 0);

	EPWM_DisableDeadZone(EPWM_CH_0_MSK | EPWM_CH_1_MSK |
						 EPWM_CH_2_MSK | EPWM_CH_3_MSK |
						 EPWM_CH_4_MSK | EPWM_CH_5_MSK);	/*关闭死区*/


	/*
	(3)设置EPWM反向输出
	*/
	EPWM_DisableReverseOutput( EPWM_CH_0_MSK | EPWM_CH_1_MSK |
							   EPWM_CH_2_MSK | EPWM_CH_3_MSK |
							   EPWM_CH_4_MSK | EPWM_CH_5_MSK );				/*关闭反相输出*/

	/*
	(4)设置EPWM加载方式
	*/
	EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK | EPWM_CH_2_MSK | EPWM_CH_4_MSK);	/*设置为自动加载模式*/
	EPWM_ConfigLoadAndIntMode(EPWM0, EPWM_EACH_PERIOD_ZERO);			/*加载点设置为每个周期点和零点*/
	EPWM_ConfigLoadAndIntMode(EPWM2, EPWM_EACH_PERIOD_ZERO);
	EPWM_ConfigLoadAndIntMode(EPWM4, EPWM_EACH_PERIOD_ZERO);			
		

	/*
	(5)设置EPWM刹车
	*/
    EPWM_AllBrakeDisable();

	/*(6)设置中断
	*/
	EPWM_EnablePeriodInt(EPWM_CH_0_MSK);								/*开启中断*/		
	
	
	/*
	(6)设置触发比较器
	*/	
	EPWM_ConfigCompareTriger(EPWM_CMPTG_0,EPWM_CMPTG_FALLING,EPWM_CMPTG_EPWM0,1000);
	
	
	/*
	(7)设置IO口输出
	*/	
    SYS_SET_IOCFG(IOP01CFG, SYS_IOCFG_P01_EPWM0); 
	SYS_SET_IOCFG(IOP04CFG, SYS_IOCFG_P04_EPWM1);
	SYS_SET_IOCFG(IOP05CFG, SYS_IOCFG_P05_EPWM2);

    SYS_SET_IOCFG(IOP06CFG,SYS_IOCFG_P06_EPWM3);	
    SYS_SET_IOCFG(IOP07CFG,SYS_IOCFG_P07_EPWM4);
    SYS_SET_IOCFG(IOP47CFG,SYS_IOCFG_P47_EPWM5);	
	

	EPWM_EnableChannelRemap(EPWM0, IPG0);				/*可实现任意的映射输出*/	
	EPWM_EnableChannelRemap(EPWM1, IPG2);
	EPWM_EnableChannelRemap(EPWM2, IPG4);
	EPWM_EnableChannelRemap(EPWM3, IPG1);
	EPWM_EnableChannelRemap(EPWM4, IPG3);
	EPWM_EnableChannelRemap(EPWM5, IPG5);
	
	EPWM_EnableOutput(EPWM_CH_0_MSK | EPWM_CH_1_MSK |
					  EPWM_CH_2_MSK | EPWM_CH_3_MSK |
					  EPWM_CH_4_MSK | EPWM_CH_5_MSK );

	/*
	(8)开启EPWM
	*/		
	EPWM_Start(EPWM_CH_0_MSK | EPWM_CH_2_MSK | EPWM_CH_4_MSK);
}

#endif // DEBUG


/*------------------------------------test------------------------------------*/
