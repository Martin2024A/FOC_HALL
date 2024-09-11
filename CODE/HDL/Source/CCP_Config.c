
/*----------------------------------include-----------------------------------*/
#include "CCP_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void CCP_Init(void)
{
	/*
	(1)设置CCP的时钟
	*/
	SYS_EnablePeripheralClk(SYS_CLK_CCP_MSK);						/*开启CCP模块时钟*/
	CCP_ConfigCLK(CCP1,CCP_CLK_DIV_64,CCP_RELOAD_CCPLOAD,4800);		/*Fccp = 48Mhz /64 = 0.75Mh ->捕获计数周期 = 4800/0.75Mhz = 6400us*/
	
	/*
	(2)设置CCP运行模式
	*/
	CCP_EnableCAPMode1();								/*设置CCP模块工作模式为捕获模式1*/
	CCP_ConfigCAPMode1(CAP0,CCP_CAP_MODE1_BOTH_EDGE);		/*设置捕获通道为CAP0，上升沿捕获*/

	/*
	(3)设置CCP捕获通道
	*/
	CCP_SelCAPMode1Channel(CAP0,ECAP10);				/*CAP0通道选择连接外部ECAP02接口*/
	SYS_SET_IOCFG(IOP31CFG,SYS_IOCFG_P31_ECAP10);		/*设置P15为ECAP02*/
	CCP_SelCAPMode1Channel(CAP0,ECAP11);
	SYS_SET_IOCFG(IOP32CFG,SYS_IOCFG_P32_ECAP11);
	CCP_SelCAPMode1Channel(CAP0,ECAP12);
	SYS_SET_IOCFG(IOP34CFG,SYS_IOCFG_P34_GECAP12);     //宏定义名称写错了？
	/*
	(4)设置CCP捕获中断
	*/		
	CCP_EnableOverflowInt(CCP1);					   /*开启CCP1溢出中断*/
	CCP_EnableCAPMode1Int(CAP0);					   /*开启CAP0通道捕获中断*/
	NVIC_EnableIRQ(CCP_IRQn);	
	/*
	(5)设置CCP 中断优先级
	*/	
	NVIC_SetPriority(CCP_IRQn,3);					/*优先级0~3， 0最高、3最低*/		
	/*
	(6)开启CCP模块
	*/	
	CCP_EnableRun(CCP1);			
	CCP_Start(CCP1);				
}


/*------------------------------------test------------------------------------*/
