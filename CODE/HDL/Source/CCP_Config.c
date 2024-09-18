
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
	CCP_EnableCAPMode1();									/*设置CCP模块工作模式为捕获模式1*/
	CCP_ConfigCAPMode1(CAP0,CCP_CAP_MODE1_BOTH_EDGE);		/*设置捕获通道为CAP0，上升沿捕获*/
	CCP_ConfigCAPMode1(CAP1,CCP_CAP_MODE1_BOTH_EDGE);		
	CCP_ConfigCAPMode1(CAP2,CCP_CAP_MODE1_BOTH_EDGE);		

	/*
	(3)设置CCP捕获通道
	*/
	CCP_SelCAPMode1Channel(CAP0,ECAP10);				/*CAP0通道选择连接外部ECAP02接口*/
	SYS_SET_IOCFG(IOP31CFG,SYS_IOCFG_P31_ECAP10);		/*设置P15为ECAP02*/

	CCP_SelCAPMode1Channel(CAP1,ECAP11);
	SYS_SET_IOCFG(IOP32CFG,SYS_IOCFG_P32_ECAP11);

	CCP_SelCAPMode1Channel(CAP2,ECAP12);
	SYS_SET_IOCFG(IOP34CFG,SYS_IOCFG_P34_GECAP12);     //宏定义名称写错了？
	/*
	(4)设置CCP捕获中断
	*/		
	CCP_EnableOverflowInt(CCP1);					   /*开启CCP1溢出中断*/
	CCP_EnableCAPMode1Int(CAP0);					   /*开启CAP0通道捕获中断*/
	CCP_EnableCAPMode1Int(CAP1);					   /*开启CAP1通道捕获中断*/
	CCP_EnableCAPMode1Int(CAP2);					   /*开启CAP2通道捕获中断*/
		
	/*
	(5)设置CCP 中断优先级
	*/	
	
	/*
	(6)开启CCP模块
	*/	
	CCP_EnableRun(CCP1);			
	CCP_Start(CCP1);				
}

uint8_t CCP_GetPrescaler(void)
{
    uint32_t temp;
    const uint8_t prescalerLookup[4] = {1, 4, 16, 64}; // 预分频查找表

    // 读取CCP->CON1寄存器的第4、5位
    temp = (CCP->CON1 >> 4) & 0x03;

    // 返回相应的预分频值
    return prescalerLookup[temp];
}

/*------------------------------------test------------------------------------*/
