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
 **			��ȡHSI״̬
 ** \param [in] none			
 ** \return  0:��ֹ����δ�ȶ�  1���ȶ�
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
 **			��ȡCPU��λ��־
 ** \param [in] none			
 ** \return  0:δ��λ  1����λ
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetCPUResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_CPURS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_GetMCUResetFlag
 **			��ȡMCU��λ��־
 ** \param [in] none			
 ** \return  0:δ��λ  1����λ
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetMCUResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_MCURS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_GetWDTResetFlag
 **			��ȡWDT��λϵͳ��־
 ** \param [in] none			
 ** \return  0:WDTδ��λϵͳ  1��WDT��λϵͳ
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetWDTResetFlag( void)
{
	return((SYSCON->RSTSTAT & SYS_RSTSTAT_WDTRS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	WWDT_GetWWDTResetFlag
 **			��ȡWWDT��λϵͳ��־
 ** \param [in] none			
 ** \return  0:WWDTδ��λϵͳ  1��WWDT��λϵͳ
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetWWDTResetFlag( void)
{
	return((WWDT->CON & WWDT_WWDTCON_WWDTRF_Msk)? 1:0);	
}

/*****************************************************************************
 ** \brief	SYS_EnableClkOutput
 **			ʹ��ϵͳʱ�����
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
 **			�ر�ϵͳʱ�����
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
 **			����ϵͳʱ�����
 ** \param [in] ClkSel : (1)SYS_CLK_OUT_SEL_AHB		
 **						 (2)SYS_CLK_OUT_SEL_HSI
 **				ClkDiv : 0~255   ʱ�������Ƶ
 ** \return  none
 ** \note	0: FCLKO=FSEL ��1~255: FCLKO=FSEL/(2��DIV)
*****************************************************************************/
void  SYS_ConfigClkOutput(uint32_t ClkSel , uint32_t ClkDiv)
{
	SYSCON->CLKODIV  &= ~(SYS_CLKODIV_CLKSEL_Msk | SYS_CLKODIV_DIV_Msk ); 
	SYSCON->CLKODIV  |= ClkSel | ClkDiv;
}
/*****************************************************************************
 ** \brief	SYS_EnableHSI
 **			ʹ�ܸ���ʱ��
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
 **			�رո���ʱ��
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
 **			���ø���ʱ��
 ** \param [in] HSISel: (1)SYS_CLK_HSI_64M
 **						(2)SYS_CLK_HSI_48M
 ** \return  none
 ** \note �л���ͬ��HSI Ƶ��ʱ����ҪԼ125us��4~5*TLSI�������л�����ѡ��Ƶ�ʣ�
 **		  �ڴ��ڼ䣬CPU ��ͣ���С�
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
 **			����TRIM��������Ƶ��
 ** \param [in] AdjValue: 0~255
 ** \return  none
 ** \note  �ϵ��ı�CLKCON[0]λʱ��ϵͳ�Զ����س���ʱ���޵�ֵ
*****************************************************************************/
void  SYS_EnableTRIMAdjustHSI(uint32_t AdjValue)
{
	SYSCON->HSI_TRIM = SYS_CLKSEL_WRITE_KEY | AdjValue;
}
/*****************************************************************************
 ** \brief	SYS_ConfigAHBClock
 **			����AHBʱ��
 ** \param [in] ClkSel :(1)SYS_CLK_SEL_HSI
 **						(2)SYS_CLK_SEL_LSI
 **				ClkDiv ��0~ 255	
 ** \return  none
 ** \note	(1) 0: HCLK = FSYS �� 1~255: HCLK = FSYS/(2��DIV)
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
 **			����APBʱ��
 ** \param [in] ClkDiv ��0~255				
 ** \return  none
 ** \note	(1) 0: PCLK = HCLK�� 1~255: PCLK = HCLK/(2��DIV)
*****************************************************************************/
void  SYS_ConfigAPBClock( uint32_t ClkDiv)
{
	SYSCON->APBCKDIV = ClkDiv;
}

/*****************************************************************************
 ** \brief	SYS_EnableLVD
 **		 ����LVD ���
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
 **		 �ر�LVD ���
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
 **			����LVD��ѹ
 ** \param [in] LVDLevel��(1)SYS_LVD_2V		LVD����ѹѡ��2V
 **						  (2)SYS_LVD_2P2V	LVD����ѹѡ��2.2V
 **						  (3)SYS_LVD_2P4V	LVD����ѹѡ��2.4V
 **						  (4)SYS_LVD_2P7V	LVD����ѹѡ��2.7
 **						  (5)SYS_LVD_3V		LVD����ѹѡ��3V
 **						  (6)SYS_LVD_3P7V	LVD����ѹѡ��3.7	
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
 **			ʹ��LVD�ж�
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
 **			�ر�LVD�ж�
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
 **			��ȡLVD�ж�״̬��־
 ** \param [in] none			
 ** \return  0��δ�����ж� 1��ʹ�ܲ������ж�
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetLVDIntFlag(void)
{
	return((SYSCON->SYS_MIS & SYS_MIS_LVDMIS_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_ClearLVDIntFlag
 **			���LVD�ж�״̬��־
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
 **			��ȡLVD״̬��־
 ** \param [in] none			
 ** \return  1��LVD����VDD 0��LVDС��VDD
 ** \note	
*****************************************************************************/
uint32_t  SYS_GetLVDStateFlag(void)
{
	return ((SYSCON->LVDCON & SYS_LVDCON_LVDF_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	SYS_EnableSARMProtect
 **			����SRAM����
 ** \param [in] SRAMAddrMask :(1) SYS_SRAM_PORTECT_2K_4K_MSK 	RAM��2K~4K��ַ��Χд����
 **							  (2) SYS_SRAM_PORTECT_4K_6K_MSK	SRAM��4K~6K��ַ��Χд����
 **							  (3) SYS_SRAM_PORTECT_6K_8K_MSK	SRAM��6K~8K��ַ��Χд����
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
 **			�ر�SRAM����
 ** \param [in] SRAMAddrMask :(1) SYS_SRAM_PORTECT_2K_4K_MSK 	RAM��2K~4K��ַ��Χд����
 **							  (2) SYS_SRAM_PORTECT_4K_6K_MSK	SRAM��4K~6K��ַ��Χд����
 **							  (3) SYS_SRAM_PORTECT_6K_8K_MSK	SRAM��6K~8K��ַ��Χд����
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
 **			�ر�����ʱ��
 ** \param [in] Module    :(1)SYS_CLK_ADCB_MSK	: 		 ADCBʱ��ʹ��λ
 **						  (2)SYS_CLK_ACMP_MSK	:		ģ��Ƚ���ʱ��ʹ��λ				  
 **						  (3)SYS_CLK_OPA_PGA_MSK:	�˷�/PGAʱ��ʹ��λ	
 **						  (4)SYS_CLK_EPWM_MSK:		EPWMʱ��ʹ��λ	
 **						  (5)SYS_CLK_CRC_MSK:		CRCʱ��ʹ��λ	
 **						  (6)SYS_CLK_WWDT_MSK:		WWDTʱ��ʹ��λ	
 **						  (7)SYS_CLK_CCP_MSK:		����/PWMʱ��ʹ��λ	
 **						  (8)SYS_CLK_ADC0_MSK:		ADC0ʱ��ʹ��λ	
 **						  (9)SYS_CLK_SSP_MSK:		SSPʱ��ʹ��λ	
 **						  (10)SYS_CLK_I2C_MSK:		I2Cʱ��ʹ��λ	
 **						  (11)SYS_CLK_UART1_MSK:	UART1ʱ��ʹ��λ	
 **						  (12)SYS_CLK_UART0_MSK:	UART0ʱ��ʹ��λ	
 **						  (13)SYS_CLK_HWDIVCE_MSK:	Ӳ��������ʱ��ʹ��λ	
 **						  (14)SYS_CLK_TIMER01_MSK:	��ʱ��01ʱ��ʹ��λ	
 **						  (15)SYS_CLK_TIMER23_MSK:	��ʱ��23ʱ��ʹ��λ											
 **						  (16)SYS_CLK_WDT_MSK:		WDTʱ��ʹ��λ		
 ** \return  none
 ** \note	 
*****************************************************************************/	
void 	SYS_DisablePeripheralClk(uint32_t Module)
{
	SYSCON->APBCKEN &= ~(Module);	
}
/*****************************************************************************
 ** \brief	SYS_EnablePeripheralClk
 **			��������ʱ��
 ** \param [in] Module    :(1)SYS_CLK_ADCB_MSK	: 		 ADCBʱ��ʹ��λ
 **						  (2)SYS_CLK_ACMP_MSK	:		ģ��Ƚ���ʱ��ʹ��λ				  
 **						  (3)SYS_CLK_OPA_PGA_MSK:	�˷�/PGAʱ��ʹ��λ	
 **						  (4)SYS_CLK_EPWM_MSK:		EPWMʱ��ʹ��λ	
 **						  (5)SYS_CLK_CRC_MSK:		CRCʱ��ʹ��λ	
 **						  (6)SYS_CLK_WWDT_MSK:		WWDTʱ��ʹ��λ	
 **						  (7)SYS_CLK_CCP_MSK:		����/PWMʱ��ʹ��λ	
 **						  (8)SYS_CLK_ADC0_MSK:		ADC0ʱ��ʹ��λ	
 **						  (9)SYS_CLK_SSP_MSK:		SSPʱ��ʹ��λ	
 **						  (10)SYS_CLK_I2C_MSK:		I2Cʱ��ʹ��λ	
 **						  (11)SYS_CLK_UART1_MSK:	UART1ʱ��ʹ��λ	
 **						  (12)SYS_CLK_UART0_MSK:	UART0ʱ��ʹ��λ	
 **						  (13)SYS_CLK_HWDIVCE_MSK:	Ӳ��������ʱ��ʹ��λ	
 **						  (14)SYS_CLK_TIMER01_MSK:	��ʱ��01ʱ��ʹ��λ	
 **						  (15)SYS_CLK_TIMER23_MSK:	��ʱ��23ʱ��ʹ��λ											
 **						  (16)SYS_CLK_WDT_MSK:		WDTʱ��ʹ��λ	
 ** \return  none
 ** \note	 
*****************************************************************************/	
void 	SYS_EnablePeripheralClk(uint32_t Module)
{
	SYSCON->APBCKEN |= (Module);	
}

/*****************************************************************************
 ** \brief	SYS_EnableTEMP
 **			ʹ���¶ȼ��
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
 **			�ر��¶ȼ��
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
 **			ʹ���ڲ�Config�����¶ȴ�����
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
 **			ʹ��TSVADJ(�¶ȴ������޵�λ)�����¶ȴ�����
 ** \param [in] none			
 ** \return  none
 ** \note	
*****************************************************************************/
void SYS_EnableTSVADJConfigAdjust(uint32_t tsvadj)
{
	SYSCON->LVDCON &= ~( SYS_LVDCON_TSVADJ_Msk);	
	SYSCON->LVDCON |= (SYS_LVDCON_TSVAS_Msk | ((0xf & tsvadj)<<SYS_LVDCON_TSVADJ_Pos));
}

