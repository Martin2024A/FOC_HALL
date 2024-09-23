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
/** \file adc1.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "adc1.h"
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

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/*****************************************************************************
 ** \brief	ADC1_ConfigRunMode
 **			设置ADC运行模式
 ** \param [in] ConvertMode:(1)ADC1_CONVERT_SINGLE			
 **							(2)ADC1_CONVERT_CONTINUOUS
 **				ClkDiv :(1)ADC1_CLK_DIV_1
 **						(2)ADC1_CLK_DIV_2
 **						(3)ADC1_CLK_DIV_4
 **						(4)ADC1_CLK_DIV_8
 **						(5)ADC1_CLK_DIV_16
 **						(6)ADC1_CLK_DIV_32
 **						(7)ADC1_CLK_DIV_64
 **						(8)ADC1_CLK_DIV_128
 **				HoldTime:(1)ADC1_HOLD_3P5_CLK
 **						 (2)ADC1_HOLD_4P5_CLK
 **						 (3)ADC1_HOLD_6P5_CLK
 **						 (4)ADC1_HOLD_10P5_CLK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ConfigRunMode(uint32_t ConvertMode, uint32_t ClkDiv,uint32_t HoldTime)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCON &= ~(ADC1_CON_ADCMS_Msk|ADC1_CON_ADCDIV_Msk|ADC1_CON_ADCSHT_Msk);
	ADC1->ADCCON |= ConvertMode |  ClkDiv | HoldTime;	
	ADC1->ADCLOCK = 0x00;
}

/*****************************************************************************
 ** \brief	ADC1_EnableScanChannel
 **			开启ADC1转换通道
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableScanChannel(uint32_t ChannelMask)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCSCAN |= ChannelMask;
	ADC1->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC1_DisableScanChannel
 **			关闭ADC1转换通道
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableScanChannel(uint32_t ChannelMask)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCSCAN &= ~(ChannelMask);
	ADC1->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC1_SetAN30Channel
 **			设置AN30内部模拟源
 ** \param [in] AN30Channel: (1)ADC1_CH_30_BG 
 **							 (2)ADC1_CH_30_OP0O
 **							 (3)ADC1_CH_30_OP1O
 **							 (4)ADC1_CH_30_PGA0O
 **							 (5)ADC1_CH_30_PGA1O
 **							 (6)ADC1_CH_30_VREF_VSS
 **							 (7)ADC1_CH_30_VREF_VDD
 **							 (8)ADC1_CH_30_VSS
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_SetAN30Channel(uint32_t AN30Channel)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON &= ~(ADC1_CON_ADCICHS_Msk);
	ADC1->ADCCON |= AN30Channel;		
	ADC1->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC1_GetResult
 **			获取ADC1转换结果
 ** \param [in] Channel: ADC1_CH_0 ~ ADC1_CH_30
 ** \return  12 bits Value
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetResult(uint32_t Channel)
{
	return(ADC1->ADCDATA[Channel]);
}

/*****************************************************************************
 ** \brief	ADC1_EnableHardwareTrigger
 **			开启硬件触发ADC1转换功能
 ** \param [in] TriggerSource: (1)ADC1_TG_EXT_FALLING
 **							(2)ADC1_TG_EXT_RISING
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableHardwareTrigger(uint32_t TriggerSource)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	switch(TriggerSource)
	{
		case ADC1_TG_EXT_FALLING:
		case ADC1_TG_EXT_RISING:
			ADC1->ADCHWTG |= TriggerSource;
			break;
		case ADC1_TG_EPWM_CMP0:
		case ADC1_TG_EPWM_CMP1:
			ADC1->ADCHWTG |= TriggerSource;
			break;

		default:
			break;
	}	
	ADC1->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC1_EnableEPWMCmp0TiggerChannel
 **			使能 EPWM 比较器0 触发的ADC1转换通道
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note  
*****************************************************************************/
void ADC1_EnableEPWMCmp0TiggerChannel(uint32_t ChannelMask)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCHPTG0 |=(ChannelMask);	
	ADC1->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC1_DisableHardwareTrigger
 **			关闭硬件触发ADC1转换功能
 ** \param [in] TriggerSource: (1)ADC1_TG_EXT_FALLING
 **								(2)ADC1_TG_EXT_RISING
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableHardwareTrigger(uint32_t TriggerSource)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	switch(TriggerSource)
	{
		case ADC1_TG_EXT_FALLING:
		case ADC1_TG_EXT_RISING:
			ADC1->ADCHWTG &= ~(ADC1_HWTG_ADCEXTEN_Msk);
			break;
		default:
			break;
	}	
	ADC1->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC1_EnableCompare
 **			开启ADC1比较功能
 ** \param [in]none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableCompare(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCMP0	|= ADC1_CMP_ADCCMPEN_Msk;
	ADC1->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC1_DisableCompare
 **			关闭ADC1比较功能
 ** \param [in] Compare : ADC1_CMP0 、ADC1_CMP1
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableCompare(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCMP0	&= ~(ADC1_CMP_ADCCMPEN_Msk);
	ADC1->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC1_ConfigCompare
 **			配置ADC1比较功能
 ** \param [in]  CmpMode:(1)ADC1_CMP_LESS_THAN_RESULT
 **						(2)ADC1_CMP_NOT_LESS_THAN_RESULT
 **				 CmpCount: 0x00~0xf  预设比较次数
 **				 CmpChannel: ADC1_CH_0 ~ ADC1_CH_30
 **				 CmpData : 12 bit 比较值
 ** \return  none
 ** \note	当内部计数器等于ADCCMPxMCNT+1的值时产生ADC比较事件。
*****************************************************************************/
void ADC1_ConfigCompare( uint32_t CmpMode, uint32_t CmpCount,  
						uint32_t CmpChannel, uint32_t CmpData)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCMP0	&= ~(ADC1_CMP_ADCCMPCOND_Msk | ADC1_CMP_ADCCMPMCNT_Msk|
							 ADC1_CMP_ADCCMPCHS_Msk | ADC1_CMP_ADCCMPDATA_Msk);
	ADC1->ADCCMP0	|= CmpMode | ((0xf & CmpCount)<<ADC1_CMP_ADCCMPMCNT_Pos) | ((0x1f& CmpChannel)<<ADC1_CMP_ADCCMPCHS_Pos)|
							(0xfff & CmpData) ;
	ADC1->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC1_GetCompareResult
 **			获取ADC1比较器结果
 ** \param [in] Compare : ADC1_CMP0 、ADC1_CMP1
 ** \return  1 /0
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareResult(uint32_t Compare)
{
	return((ADC1->ADCCMP0 & ADC1_CMP_ADCCMPO_Msk)? 1:0);
}


/*****************************************************************************
 ** \brief	ADC1_Start
 **			开启ADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_Start(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON |= ADC1_CON_ADCEN_Msk;
	ADC1->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC1_Stop
 **			关闭ADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_Stop(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON &= ~(ADC1_CON_ADCEN_Msk);
	ADC1->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC1_StartAdjust
 **			开启ADC1校准
 ** \param [in] none
** \return  none
 ** \note	
*****************************************************************************/
void ADC1_StartAdjust(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON2 |= (ADC1_CON2_ADCCALEN_Msk);
	ADC1->ADCLOCK = 0x00;	
	while(ADC1->ADCCON2 & ADC1_CON2_ADCCALEN_Msk);
}

/*****************************************************************************
 ** \brief	ADC1_EnableAdjust
 **			开启ADC1带有校准数据的ADC转换
 ** \param [in] none
 ** \return   none
 ** \note	
*****************************************************************************/
void ADC1_EnableAdjust(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON2 &= ~(ADC1_CON2_ADCCALCONV_Msk);
	ADC1->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC1_DisableAdjust
 **			关闭ADC1带有校准数据的ADC转换
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableAdjust(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON2 |= (ADC1_CON2_ADCCALCONV_Msk);
	ADC1->ADCLOCK = 0x00;
}

/*****************************************************************************
 ** \brief	ADC1_EnableReset
 **			复位ADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableReset(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON |= ADC1_CON_ADCRST_Msk;
	ADC1->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC1_GetConvertErrorFlag
 **			获取ADC1 转换错误标志位
 ** \param [in] none
 ** \return  1 ：转换出现错误	0：无错误
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetConvertErrorFlag(void)
{
	return((ADC1->ADCCON & ADC1_CON_ADCCONVER_Msk)? 1:0);	
}
/*****************************************************************************
 ** \brief	ADC1_GetAdjustErrorFlag
 **			获取ADC1 校准错误标志位
 ** \param [in] none
 ** \return  1 ：校准出现错误	0：无错误
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetAdjustErrorFlag(void)
{
	return((ADC1->ADCCON & ADC1_CON_ADCCALERR_Msk)? 1:0);	
}

/*****************************************************************************
 ** \brief	ADC1_ClearConvertErrorFlag
 **			清除ADC1 转换错误标志位
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearConvertErrorFlag(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON |= ADC1_CON_ADCCONVERRCLR_Msk;
	ADC1->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC1_ClearAdjustErrorFlag
 **			清除ADC1 校准错误标志位
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearAdjustErrorFlag(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON |= ADC1_CON_ADCCALERRCLR_Msk;
	ADC1->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC1_EnableCompareInt
 **			开启ADC1比较中断
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void ADC1_EnableCompareInt(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCIMSC |= ADC1_IMSC_IMSC31_Msk;
	ADC1->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC1_DisableCompareInt
 **			关闭ADC1比较中断
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableCompareInt(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCIMSC &= ~(ADC1_IMSC_IMSC31_Msk);
	ADC1->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC1_GetCompareIntFlag
 **			获取ADC1比较中断使能并且产生中断标志位
 ** \param [in] none
 ** \return  1:中断使能并且产生中断 0：无中断
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareIntFlag(void)
{
	return((ADC1->ADCMIS & ADC1_MIS_MIS31_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	ADC1_ClearCompareIntFlag
 **			清除ADC1比较中断标志位
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearCompareIntFlag(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCICLR |= (ADC1_ICLR_ICLR31_Msk);
	ADC1->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC1_EnableChannelInt
 **			开启ADC1通道n中断
 ** \param [in]ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableChannelInt(uint32_t ChannelMask)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCIMSC |= ChannelMask ;
	ADC1->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC1_DisableChannelInt
 **			关闭ADC1通道n中断
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableChannelInt(uint32_t ChannelMask)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCIMSC &= ~(ChannelMask);
	ADC1->ADCLOCK = 0x00;
}
/*****************************************************************************
 ** \brief	ADC1_GetChannelIntFlag
 **			获取ADC1通道n中断使能并且产生中断标志位
 ** \param [in] Channel:ADC1_CH_0 ~ ADC1_CH_30
 ** \return  1:中断使能并且产生中断 0：无中断
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetChannelIntFlag(uint32_t Channel)
{
	return((ADC1->ADCMIS & (0x1UL<<Channel))? 1:0);	
}
/*****************************************************************************
 ** \brief	ADC1_ClearChannelIntFlag
 **			清除ADC1通道n中断标志位
 ** \param [in] Channel:ADC1_CH_0 ~ ADC1_CH_30
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearChannelIntFlag(uint32_t Channel)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCICLR |= (0x01UL<< Channel);
	ADC1->ADCLOCK = 0x00;			
}
