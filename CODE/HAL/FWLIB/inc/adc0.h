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

/*****************************************************************************/
/** \file adc0.h
**
** History:
** 
*****************************************************************************/
#ifndef __ADC0_H_
#define __ADC0_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "CMS32M55xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **ADC0 时钟
-----------------------------------------------------------------------------*/
#define		ADC0_CLK_DIV_1		(0x0UL)			/*Fadc = Fapb / 1*/
#define		ADC0_CLK_DIV_2		(0x1UL)			/*Fadc = Fapb / 2*/
#define		ADC0_CLK_DIV_4		(0x2UL)			/*Fadc = Fapb / 4*/			
#define		ADC0_CLK_DIV_8		(0x3UL)			/*Fadc = Fapb / 8*/
#define		ADC0_CLK_DIV_16		(0x4UL)			/*Fadc = Fapb / 16*/			
#define		ADC0_CLK_DIV_32		(0x5UL)			/*Fadc = Fapb / 32*/
#define		ADC0_CLK_DIV_64		(0x6UL)			/*Fadc = Fapb / 64*/
#define		ADC0_CLK_DIV_128	(0x7UL)			/*Fadc = Fapb / 128*/
/*----------------------------------------------------------------------------
 **ADC0 转换模式             
-----------------------------------------------------------------------------*/
#define		ADC0_CONVERT_SINGLE				(0x0UL)			/*对指定通道执行一次A/D 转换*/
#define		ADC0_CONVERT_CONTINUOUS			(0x1UL<<ADC0_CON_ADcms_Pos)	/*对所有选定的通道都执行A/D 转换*/
/*----------------------------------------------------------------------------
 **ADC0 外部触发边沿选择
-----------------------------------------------------------------------------*/
#define		ADC0_TG_EXT_FALLING			((0x0UL)|ADC0_HWTG_ADCEXT0TEN_Msk)		/*外部硬件下降沿触发*/		
#define		ADC0_TG_EXT_RISING			((0x1UL<<ADC0_HWTG_ADCEXT0TES_Pos)|ADC0_HWTG_ADCEXT0TEN_Msk)	/*外部硬件上升沿触发*/		

/*----------------------------------------------------------------------------
 **ADC0 内部触发源选择
-----------------------------------------------------------------------------*/
#define		ADC0_TG_INTNEL_ADC0				(0x0UL | ADC0_HWTG_ADCINTTGEN_Msk)		/*内部ADC0触发*/		
#define		ADC0_TG_INTNEL_ADCB				((0x1UL<<ADC0_HWTG_ADCINTTGSS_Pos)| ADC0_HWTG_ADCINTTGEN_Msk)	/*内部ADC1触发*/
#define		ADC0_TG_INTNEL_ACMP0			((0x2UL<<ADC0_HWTG_ADCINTTGSS_Pos)| ADC0_HWTG_ADCINTTGEN_Msk)	/*内部ACMP0事件触发*/			
#define		ADC0_TG_INTNEL_ACMP1			((0x3UL<<ADC0_HWTG_ADCINTTGSS_Pos)| ADC0_HWTG_ADCINTTGEN_Msk)	/*内部ACMP1事件触发*/		
#define		ADC0_TG_INTNEL_TMR0				((0x4UL<<ADC0_HWTG_ADCINTTGSS_Pos)| ADC0_HWTG_ADCINTTGEN_Msk)	/*内部TMR0已使能中断触发*/				
#define		ADC0_TG_INTNEL_TMR1				((0x5UL<<ADC0_HWTG_ADCINTTGSS_Pos)| ADC0_HWTG_ADCINTTGEN_Msk)	/*内部TMR1已使能中断触发*/		

/*----------------------------------------------------------------------------
 **ADC0 采样通道
-----------------------------------------------------------------------------*/
#define		ADC0_CH_0					(0x0UL)			
#define		ADC0_CH_1					(0x1UL)	
#define		ADC0_CH_2					(0x2UL)			
#define		ADC0_CH_3					(0x3UL)			
#define		ADC0_CH_4					(0x4UL)		
#define		ADC0_CH_5					(0x5UL)			
#define		ADC0_CH_6					(0x6UL)	
#define		ADC0_CH_7					(0x7UL)			
#define		ADC0_CH_8					(0x8UL)			
#define		ADC0_CH_9					(0x9UL)		
#define		ADC0_CH_10					(0xAUL)			
#define		ADC0_CH_11					(0xBUL)	
#define		ADC0_CH_12					(0xCUL)			
#define		ADC0_CH_13					(0xDUL)			
#define		ADC0_CH_14					(0xEUL)		
#define		ADC0_CH_15					(0xFUL)			
#define		ADC0_CH_16					(0x10UL)	
#define		ADC0_CH_17					(0x11UL)			
#define		ADC0_CH_18					(0x12UL)			
#define		ADC0_CH_19					(0x13UL)
#define		ADC0_CH_20					(0x14UL)
#define		ADC0_CH_21					(0x15UL)
#define		ADC0_CH_22					(0x16UL)
#define		ADC0_CH_23					(0x17UL)
#define		ADC0_CH_24					(0x18UL)
#define		ADC0_CH_25					(0x19UL)
#define		ADC0_CH_26					(0x1AUL)
#define		ADC0_CH_27					(0x1BUL)
#define		ADC0_CH_28					(0x1CUL)
#define		ADC0_CH_29					(0x1DUL)


#define		ADC0_CH_0_MSK				(0x1UL)			
#define		ADC0_CH_1_MSK				(0x2UL)	
#define		ADC0_CH_2_MSK				(0x4UL)			
#define		ADC0_CH_3_MSK				(0x8UL)			
#define		ADC0_CH_4_MSK				(0x10UL)		
#define		ADC0_CH_5_MSK				(0x20UL)			
#define		ADC0_CH_6_MSK				(0x40UL)	
#define		ADC0_CH_7_MSK				(0x80UL)			
#define		ADC0_CH_8_MSK				(0x100UL)			
#define		ADC0_CH_9_MSK				(0x200UL)		
#define		ADC0_CH_10_MSK				(0x400UL)			
#define		ADC0_CH_11_MSK				(0x800UL)	
#define		ADC0_CH_12_MSK				(0x1000UL)			
#define		ADC0_CH_13_MSK				(0x2000UL)			
#define		ADC0_CH_14_MSK				(0x4000UL)		
#define		ADC0_CH_15_MSK				(0x8000UL)			
#define		ADC0_CH_16_MSK				(0x10000UL)	
#define		ADC0_CH_17_MSK				(0x20000UL)			
#define		ADC0_CH_18_MSK				(0x40000UL)			
#define		ADC0_CH_19_MSK				(0x80000UL)
/*----------------------------------------------------------------------------
 **ADC0 	AN30选择内部模拟通道
-----------------------------------------------------------------------------*/
#define		ADC0_CH_30_BG			(0x00UL<<ADC0_CON_ADCICHS_Pos)		/*Bandgap 1.2V*/
#define		ADC0_CH_30_OP0O			(0x01UL<<ADC0_CON_ADCICHS_Pos)		/*运放0 的输出*/
#define		ADC0_CH_30_OP1O			(0x02UL<<ADC0_CON_ADCICHS_Pos)		/*运放1 的输出*/
#define		ADC0_CH_30_PGA0O		(0x03UL<<ADC0_CON_ADCICHS_Pos)		/*PGA0 的输出*/
#define		ADC0_CH_30_PGA1O		(0x04UL<<ADC0_CON_ADCICHS_Pos)		/*PGA1 的输出*/
#define		ADC0_CH_30_VREF_VSS		(0x05UL<<ADC0_CON_ADCICHS_Pos)		/*ADC 参考负端*/
#define		ADC0_CH_30_VREF_VDD		(0x06UL<<ADC0_CON_ADCICHS_Pos)		/*ADC 参考正端*/
#define		ADC0_CH_30_VSS			(0x07UL<<ADC0_CON_ADCICHS_Pos)		
/*----------------------------------------------------------------------------
 **ADC0   比较
-----------------------------------------------------------------------------*/
#define		ADC0_CMP_LESS_THAN_RESULT		(0x00UL)		/*ADC 结果<预设值*/
#define		ADC0_CMP_NOT_LESS_THAN_RESULT	(0x01UL<<ADC0_CMP0_CMP0COND_Pos)	/*ADC 结果>=预设值*/


/*----------------------------------------------------------------------------
 **ADC0   写保护
-----------------------------------------------------------------------------*/
#define		ADC0_LOCK_WRITE_KEY		(0x55UL)


/*****************************************************************************
 ** \brief	ADC0_IS_BUSY
 **			获取ADC0转换结束/空闲标志位
 ** \param [in] none
 ** \return  1：忙   0：空闲/转换完成
 ** \note	 
*****************************************************************************/
#define	ADC0_IS_BUSY()		((ADC0->ADCCON2&ADC0_CON2_ADCST_Msk)? 1:0)



/*****************************************************************************
 ** \brief	ADC0_Go
 **			开启ADC0转换
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
__STATIC_INLINE	void ADC0_Go(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCON2 |= ADC0_CON2_ADCST_Msk;
	ADC0->ADCLOCK = 0x00;
}


/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************
 ** \brief	ADC0_ConfigRunMode
 **			设置ADC0运行模式
 ** \param [in] ConvertMode:(1)ADC0_CONVERT_SINGLE			
 **							(2)ADC0_CONVERT_CONTINUOUS
 **				ClkDiv :(1)ADC0_CLK_DIV_1
 **						(2)ADC0_CLK_DIV_2
 **						(3)ADC0_CLK_DIV_4
 **						(4)ADC0_CLK_DIV_8
 **						(5)ADC0_CLK_DIV_16
 **						(6)ADC0_CLK_DIV_32
 **						(7)ADC0_CLK_DIV_64
 **						(8)ADC0_CLK_DIV_128
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ConfigRunMode(uint32_t ChannelSwitch, uint32_t ClkDiv);

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
void ADC0_SetAN30Channel(uint32_t AN30Channel);
/*****************************************************************************
 ** \brief	ADC0_EnableChannel
 **			开启ADC0转换通道
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableChannel(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC0_DisableChannel
 **			关闭ADC0转换通道
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableChannel(uint32_t ChannelMask);

/*****************************************************************************
 ** \brief	ADC0_SelSoftwareSwitchChannel
 **			选择软件切换转换的通道
 ** \param [in] Channel: ADC0_CH_0 ~ ADC0_CH_19
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_SelSoftwareSwitchChannel(uint32_t Channel);

/*****************************************************************************
 ** \brief	ADC0_GetResult
 **			获取ADC0转换结果
 ** \param [in] Channel: ADC0_CH_0 ~ ADC0_CH_19
 ** \return  12 bits Value
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetResult(uint32_t Channel);

/*****************************************************************************
 ** \brief	ADC0_EnableHardwareTrigger
 **			开启硬件触发ADC0转换功能
 ** \param [in] TriggerSource: (1)ADC0_TG_EXT_FALLING
 **							(2)ADC0_TG_EXT_RISING
 **							(3)ADC0_TG_INTNEL_ADC0
 **							(4)ADC0_TG_INTNEL_ADC1
 **							(5)ADC0_TG_INTNEL_ACMP0
 **							(6)ADC0_TG_INTNEL_ACMP1
 **							(7)ADC0_TG_INTNEL_TMR0
 **							(8)ADC0_TG_INTNEL_TMR1
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableHardwareTrigger(uint32_t TriggerSource);
/*****************************************************************************
 ** \brief	ADC0_DisableHardwareTrigger
 **			关闭硬件触发ADC0转换功能
 ** \param [in] TriggerSource: (1)ADC0_TG_EXT_FALLING
 **							(2)ADC0_TG_EXT_RISING
 **							(3)ADC0_TG_INTNEL_ADC0
 **							(4)ADC0_TG_INTNEL_ADC1
 **							(5)ADC0_TG_INTNEL_ACMP0
 **							(6)ADC0_TG_INTNEL_ACMP1
 **							(7)ADC0_TG_INTNEL_TMR0
 **							(8)ADC0_TG_INTNEL_TMR1
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableHardwareTrigger(uint32_t TriggerSource);

/*****************************************************************************
 ** \brief	ADC0_EnableCompare
 **			开启ADC0比较功能
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableCompare(void);
/*****************************************************************************
 ** \brief	ADC0_DisableCompare
 **			关闭ADC0比较功能
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableCompare(void);
/*****************************************************************************
 ** \brief	ADC0_ConfigCompare
 **			配置ADC0比较功能
 ** \param [in] CmpMode:(1)ADC0_CMP_LESS_THAN_RESULT
 **						(2)ADC0_CMP_NOT_LESS_THAN_RESULT
 **				 CmpCount: 0x00~0xf  预设比较次数
 **				 CmpChannel: ADC0_CH_0 ~ ADC0_CH_19
 **				 CmpData : 12 bit 比较值
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ConfigCompare(uint32_t CmpMode, uint32_t CmpCount,  
						uint32_t CmpChannel, uint32_t CmpData);

/*****************************************************************************
 ** \brief	ADC0_GetCompareResult
 **			获取ADC0比较器结果
 ** \param [in] none
 ** \return  1 /0
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetCompareResult(void);



/*****************************************************************************
 ** \brief	ADC0_EnableCompareInt
 **			开启ADC0比较中断
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableCompareInt(void);
/*****************************************************************************
 ** \brief	ADC0_DisableCompareInt
 **			关闭ADC0比较中断
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableCompareInt(void);
/*****************************************************************************
 ** \brief	ADC0_GetCompareIntFlag
 **			获取ADC0比较中断使能并且产生中断标志位
 ** \param [in] none
 ** \return  1:中断使能并且产生中断 0：无中断
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetCompareIntFlag(void);
/*****************************************************************************
 ** \brief	ADC0_ClearCompareIntFlag
 **			清除ADC0比较中断标志位
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ClearCompareIntFlag(void);

/*****************************************************************************
 ** \brief	ADC0_EnableChannelInt
 **			开启ADC0通道n中断
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableChannelInt(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC0_DisableChannelInt
 **			关闭ADC0通道n中断
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableChannelInt(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC0_GetChannelIntFlag
 **			获取ADC0通道n中断使能并且产生中断标志位
 ** \param [in] Channel:ADC0_CH_0 ~ ADC0_CH_19
 ** \return  1:中断使能并且产生中断 0：无中断
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetChannelIntFlag(uint32_t Channel);
/*****************************************************************************
 ** \brief	ADC0_ClearChannelIntFlag
 **			清除ADC0通道n中断标志位
 ** \param [in] Channel:ADC0_CH_0 ~ ADC0_CH_19
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ClearChannelIntFlag(uint32_t Channel);

/*****************************************************************************
 ** \brief	ADC0_Start
 **			开启ADC0
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_Start(void);
/*****************************************************************************
 ** \brief	ADC0_Stop
 **			关闭ADC0
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_Stop(void);




#ifdef __cplusplus
}
#endif

#endif /* __ADC0_H_ */

