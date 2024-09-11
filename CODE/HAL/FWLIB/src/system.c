/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/****************************************************************************/
/** \file system.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "system.h"
/****************************************************************************/
/*	Local pre-processor symbols/macros('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/


/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/
/*****************************************************************************
 ** \brief	SYS_GetHSIState
 **			获取HSI状态
 ** \param [in] none			
 ** \return  0:禁止或者未稳定  1；稳定
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetHSIState( void)
{
	return((SYSCON->CLKSTAT & SYS_CLKSTAT_IRCSTB_Msk)? 1:0);	
}

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/*****************************************************************************
 ** \brief	SYS_GetCPUResetFlag
 **			获取CPU复位标志
 ** \param [in] none			
 ** \return  0:未复位  1；复位
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetCPUResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_CPURS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_GetMCUResetFlag
 **			获取MCU复位标志
 ** \param [in] none			
 ** \return  0:未复位  1；复位
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetMCUResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_MCURS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_GetWDTResetFlag
 **			获取WDT复位系统标志
 ** \param [in] none			
 ** \return  0:WDT未复位系统  1；WDT复位系统
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetWDTResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_WDTRS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	WWDT_GetWWDTResetFlag
 **			获取WWDT复位系统标志
 ** \param [in] none			
 ** \return  0:WWDT未复位系统  1；WWDT复位系统
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetWWDTResetFlag( void)
{
	return((WWDT->CON & WWDT_WWDTCON_WWDTRF_Msk)? 1:0);	
}

/*****************************************************************************
 ** \brief	SYS_EnableClkOutput
 **			使能系统时钟输出
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_EnableClkOutput(void)
{
	SYSCON->CLKODIV  |=SYS_CLKODIV_EN_Msk; 
}
/*****************************************************************************
 ** \brief	SYS_DisableClkOutput
 **			关闭系统时钟输出
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_DisableClkOutput(void)
{
	SYSCON->CLKODIV  &= ~(SYS_CLKODIV_EN_Msk); 	
}
/*****************************************************************************
 ** \brief	SYS_ConfigClkOutput
 **			配置系统时钟输出
 ** \param [in] ClkSel : (1)SYS_CLK_OUT_SEL_AHB		
 **						 (2)SYS_CLK_OUT_SEL_HSI
 **				ClkDiv : 0~255   时钟输出分频
 ** \return  none
 ** \note	0: FCLKO=FSEL ；1~255: FCLKO=FSEL/(2×DIV)
*****************************************************************************/
void  SYS_ConfigClkOutput(uint32_t ClkSel , uint32_t ClkDiv)
{
	SYSCON->CLKODIV  &= ~(SYS_CLKODIV_CLKSEL_Msk | SYS_CLKODIV_DIV_Msk ); 
	SYSCON->CLKODIV  |= ClkSel | ClkDiv;
}
/*****************************************************************************
 ** \brief	SYS_EnableHSI
 **			使能高速时钟
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_EnableHSI(void)
{
	uint32_t Temp;
	Temp = SYSCON->CLKCON;
	Temp |= SYS_CLKCON_IRCEN_Msk;
	SYSCON->CLKCON  =  SYS_CLKSEL_WRITE_KEY | (Temp & 0xffff);
}
/*****************************************************************************
 ** \brief	SYS_DisableHSI
 **			关闭高速时钟
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_DisableHSI(void)
{
	uint32_t Temp;
	Temp = SYSCON->CLKCON;
	Temp &= ~(SYS_CLKCON_IRCEN_Msk);
	SYSCON->CLKCON  =  SYS_CLKSEL_WRITE_KEY | (Temp & 0xffff);	
}
/*****************************************************************************
 ** \brief	SYS_ConfigHSI
 **			配置高速时钟
 ** \param [in] HSISel: (1)SYS_CLK_HSI_64M
 **						(2)SYS_CLK_HSI_48M
 ** \return  none
 ** \note 切换不同的HSI 频率时，需要约125us（4~5*TLSI）才能切换到所选的频率，
 **		  在此期间，CPU 暂停运行。
*****************************************************************************/
void  SYS_ConfigHSI(uint32_t HSISel)
{
	uint32_t Temp;
	Temp = SYSCON->CLKCON;
	Temp &= ~(SYS_CLKCON_IRCSEL_Msk);
	Temp |= HSISel;
	SYSCON->CLKCON  =  SYS_CLKSEL_WRITE_KEY | (Temp & 0xffff);		
}
/*****************************************************************************
 ** \brief	SYS_EnableTRIMAdjustHSI
 **			开启TRIM调节内振频率
 ** \param [in] AdjValue: 0~255
 ** \return  none
 ** \note  上电或改变CLKCON[0]位时，系统自动加载出厂时的修调值
*****************************************************************************/
void  SYS_EnableTRIMAdjustHSI(uint32_t AdjValue)
{
	SYSCON->HSI_TRIM = SYS_CLKSEL_WRITE_KEY | AdjValue;
}
/*****************************************************************************
 ** \brief	SYS_ConfigAHBClock
 **			配置AHB时钟
 ** \param [in] ClkSel :(1)SYS_CLK_SEL_HSI
 **						(2)SYS_CLK_SEL_LSI
 **				ClkDiv ：0~ 255	
 ** \return  none
 ** \note	(1) 0: HCLK = FSYS ； 1~255: HCLK = FSYS/(2×DIV)
*****************************************************************************/
void  SYS_ConfigAHBClock(uint32_t ClkSel, uint32_t ClkDiv)
{
	uint32_t  Delay = 10000;
	do{
		if(SYS_GetHSIState())
		{
			break;
		}
	}while(Delay--);
	
	SYSCON->CLKSEL = SYS_CLKSEL_WRITE_KEY | ClkSel;
	SYSCON->AHBCKDIV = ClkDiv;
}
/*****************************************************************************
 ** \brief	SYS_ConfigAPBClock
 **			配置APB时钟
 ** \param [in] ClkDiv ：0~255				
 ** \return  none
 ** \note	(1) 0: PCLK = HCLK； 1~255: PCLK = HCLK/(2×DIV)
*****************************************************************************/
void  SYS_ConfigAPBClock( uint32_t ClkDiv)
{
	SYSCON->APBCKDIV = ClkDiv;
}

/*****************************************************************************
 ** \brief	SYS_EnableLVD
 **		 开启LVD 监测
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableLVD(void)
{
	SYSCON->LVDCON |= SYS_LVDCON_LVDE_Msk;
}
/*****************************************************************************
 ** \brief	SYS_DisableLVD
 **		 关闭LVD 监测
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_DisableLVD(void)
{
	SYSCON->LVDCON &= ~(SYS_LVDCON_LVDE_Msk);
}

/*****************************************************************************
 ** \brief	SYS_ConfigLVDLevel
 **			设置LVD电压
 ** \param [in] LVDLevel：(1)SYS_LVD_2V		LVD监测电压选择2V
 **						  (2)SYS_LVD_2P2V	LVD监测电压选择2.2V
 **						  (3)SYS_LVD_2P4V	LVD监测电压选择2.4V
 **						  (4)SYS_LVD_2P7V	LVD监测电压选择2.7
 **						  (5)SYS_LVD_3V		LVD监测电压选择3V
 **						  (6)SYS_LVD_3P7V	LVD监测电压选择3.7	
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_ConfigLVDLevel(uint32_t LVDLevel)
{
	SYSCON->LVDCON  &= ~(SYS_LVDCON_SEL_Msk);
	SYSCON->LVDCON  |= LVDLevel;
}
/*****************************************************************************
 ** \brief	SYS_EnableLVDInt
 **			使能LVD中断
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableLVDInt(void)
{
	SYSCON->SYS_IMSC |= SYS_RIS_LVDRIS_Msk;
}
/*****************************************************************************
 ** \brief	SYS_DisableLVDInt
 **			关闭LVD中断
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_DisableLVDInt(void)
{
	SYSCON->SYS_IMSC &= ~(SYS_RIS_LVDRIS_Msk);
}
/*****************************************************************************
 ** \brief	SYS_GetLVDIntFlag
 **			获取LVD中断状态标志
 ** \param [in] none			
 ** \return  0：未产生中断 1：使能并产生中断
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetLVDIntFlag(void)
{
	return((SYSCON->SYS_MIS & SYS_MIS_LVDMIS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_ClearLVDIntFlag
 **			清除LVD中断状态标志
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_ClearLVDIntFlag(void)
{
	SYSCON->SYS_ICLR |= SYS_ICLR_LVDICLR_Msk;
}
/*****************************************************************************
 ** \brief	SYS_GetLVDStateFlag
 **			获取LVD状态标志
 ** \param [in] none			
 ** \return  1：LVD大于VDD 0：LVD小于VDD
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetLVDStateFlag(void)
{
	return ((SYSCON->LVDCON & SYS_LVDCON_LVDF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_EnableSARMProtect
 **			开启SRAM保护
 ** \param [in] SRAMAddrMask :(1) SYS_SRAM_PORTECT_2K_4K_MSK 	RAM对2K~4K地址范围写保护
 **							  (2) SYS_SRAM_PORTECT_4K_6K_MSK	SRAM对4K~6K地址范围写保护
 **							  (3) SYS_SRAM_PORTECT_6K_8K_MSK	SRAM对6K~8K地址范围写保护
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_EnableSARMProtect(uint32_t SRAMAddrMask)
{
	uint32_t Temp;
	Temp = SYSCON->SRAMLOCK;
	Temp |= SRAMAddrMask;	
	SYSCON->SRAMLOCK = SYS_SRAMLOCK_WRITE_KEY | (Temp & 0xffff);
}
/*****************************************************************************
 ** \brief	SYS_DisableSARMProtect
 **			关闭SRAM保护
 ** \param [in] SRAMAddrMask :(1) SYS_SRAM_PORTECT_2K_4K_MSK 	RAM对2K~4K地址范围写保护
 **							  (2) SYS_SRAM_PORTECT_4K_6K_MSK	SRAM对4K~6K地址范围写保护
 **							  (3) SYS_SRAM_PORTECT_6K_8K_MSK	SRAM对6K~8K地址范围写保护
 ** \return  none
 ** \note	
*****************************************************************************/
void  SYS_DisableSARMProtect(uint32_t SRAMAddrMask)
{
	uint32_t Temp;
	Temp = SYSCON->SRAMLOCK;
	Temp &= ~(SRAMAddrMask);	
	SYSCON->SRAMLOCK = SYS_SRAMLOCK_WRITE_KEY | (Temp & 0xffff);	
}
/*****************************************************************************
 ** \brief	SYS_DisablePeripheralClk
 **			关闭外设时钟
 ** \param [in] Module    :(1)SYS_CLK_ADCB_MSK	: 		 ADCB时钟使能位
 **						  (2)SYS_CLK_ACMP_MSK	:		模拟比较器时钟使能位				  
 **						  (3)SYS_CLK_OPA_PGA_MSK:	运放/PGA时钟使能位	
 **						  (4)SYS_CLK_EPWM_MSK:		EPWM时钟使能位	
 **						  (5)SYS_CLK_CRC_MSK:		CRC时钟使能位	
 **						  (6)SYS_CLK_WWDT_MSK:		WWDT时钟使能位	
 **						  (7)SYS_CLK_CCP_MSK:		捕获/PWM时钟使能位	
 **						  (8)SYS_CLK_ADC0_MSK:		ADC0时钟使能位	
 **						  (9)SYS_CLK_SSP_MSK:		SSP时钟使能位	
 **						  (10)SYS_CLK_I2C_MSK:		I2C时钟使能位	
 **						  (11)SYS_CLK_UART1_MSK:	UART1时钟使能位	
 **						  (12)SYS_CLK_UART0_MSK:	UART0时钟使能位	
 **						  (13)SYS_CLK_HWDIVCE_MSK:	硬件除法器时钟使能位	
 **						  (14)SYS_CLK_TIMER01_MSK:	定时器01时钟使能位	
 **						  (15)SYS_CLK_TIMER23_MSK:	定时器23时钟使能位											
 **						  (16)SYS_CLK_WDT_MSK:		WDT时钟使能位		
 ** \return  none
 ** \note	 
*****************************************************************************/	
void 	SYS_DisablePeripheralClk(uint32_t Module)
{
	SYSCON->APBCKEN &= ~(Module);	
}
/*****************************************************************************
 ** \brief	SYS_EnablePeripheralClk
 **			开启外设时钟
 ** \param [in] Module    :(1)SYS_CLK_ADCB_MSK	: 		 ADCB时钟使能位
 **						  (2)SYS_CLK_ACMP_MSK	:		模拟比较器时钟使能位				  
 **						  (3)SYS_CLK_OPA_PGA_MSK:	运放/PGA时钟使能位	
 **						  (4)SYS_CLK_EPWM_MSK:		EPWM时钟使能位	
 **						  (5)SYS_CLK_CRC_MSK:		CRC时钟使能位	
 **						  (6)SYS_CLK_WWDT_MSK:		WWDT时钟使能位	
 **						  (7)SYS_CLK_CCP_MSK:		捕获/PWM时钟使能位	
 **						  (8)SYS_CLK_ADC0_MSK:		ADC0时钟使能位	
 **						  (9)SYS_CLK_SSP_MSK:		SSP时钟使能位	
 **						  (10)SYS_CLK_I2C_MSK:		I2C时钟使能位	
 **						  (11)SYS_CLK_UART1_MSK:	UART1时钟使能位	
 **						  (12)SYS_CLK_UART0_MSK:	UART0时钟使能位	
 **						  (13)SYS_CLK_HWDIVCE_MSK:	硬件除法器时钟使能位	
 **						  (14)SYS_CLK_TIMER01_MSK:	定时器01时钟使能位	
 **						  (15)SYS_CLK_TIMER23_MSK:	定时器23时钟使能位											
 **						  (16)SYS_CLK_WDT_MSK:		WDT时钟使能位	
 ** \return  none
 ** \note	 
*****************************************************************************/	
void 	SYS_EnablePeripheralClk(uint32_t Module)
{
	SYSCON->APBCKEN |= (Module);	
}

/*****************************************************************************
 ** \brief	SYS_EnableTEMP
 **			使能温度检测
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableTEMP(void)
{
	SYSCON->LVDCON |= SYS_LVDCON_TSVEN_Msk;
}
/*****************************************************************************
 ** \brief	SYS_DisableTEMP
 **			关闭温度检测
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_DisableTEMP(void)
{
	SYSCON->LVDCON &= ~(SYS_LVDCON_TSVEN_Msk);
}

/*****************************************************************************
 ** \brief	SYS_EnableTEMPConfigAdjust
 **			使能内部Config调节温度传感器
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableTEMPConfigAdjust(void)
{
	SYSCON->LVDCON &= ~(SYS_LVDCON_TSVAS_Msk);
}
/*****************************************************************************
 ** \brief	SYS_EnableTSVADJConfigAdjust
 **			使能TSVADJ(温度传感器修调位)调节温度传感器
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableTSVADJConfigAdjust(uint32_t tsvadj)
{
	SYSCON->LVDCON &= ~( SYS_LVDCON_TSVADJ_Msk);	
	SYSCON->LVDCON |= (SYS_LVDCON_TSVAS_Msk | ((0xf & tsvadj)<<SYS_LVDCON_TSVADJ_Pos));
}

