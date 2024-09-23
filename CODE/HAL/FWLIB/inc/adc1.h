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
/** \file adc1.h
**
** History:
** 
*****************************************************************************/
#ifndef __ADC1_H_
#define __ADC1_H_

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
 **ADC1 ʱ��
-----------------------------------------------------------------------------*/
#define		ADC1_CLK_DIV_1		(0x0UL)			/*Fadc = Fapb / 1*/
#define		ADC1_CLK_DIV_2		(0x1UL)			/*Fadc = Fapb / 2*/
#define		ADC1_CLK_DIV_4		(0x2UL)			/*Fadc = Fapb / 4*/			
#define		ADC1_CLK_DIV_8		(0x3UL)			/*Fadc = Fapb / 8*/
#define		ADC1_CLK_DIV_16		(0x4UL)			/*Fadc = Fapb / 16*/			
#define		ADC1_CLK_DIV_32		(0x5UL)			/*Fadc = Fapb / 32*/
#define		ADC1_CLK_DIV_64		(0x6UL)			/*Fadc = Fapb / 64*/
#define		ADC1_CLK_DIV_128	(0x7UL)			/*Fadc = Fapb / 128*/
/*----------------------------------------------------------------------------
 **ADC1 ��������ʱ��ѡ��
-----------------------------------------------------------------------------*/
#define		ADC1_HOLD_3P5_CLK	(0x00UL)		/*��������3.5 ��ADC clock cycles*/
#define		ADC1_HOLD_4P5_CLK	(0x01UL<<ADC1_CON_ADCSHT_Pos)	/*��������4.5 ��ADC clock cycles*/
#define		ADC1_HOLD_6P5_CLK	(0x02UL<<ADC1_CON_ADCSHT_Pos)	/*��������6.5 ��ADC clock cycles*/
#define		ADC1_HOLD_10P5_CLK	(0x03UL<<ADC1_CON_ADCSHT_Pos)	/*��������10.5 ��ADC clock cycles*/


/*----------------------------------------------------------------------------
 **ADC1 ת��ģʽ
-----------------------------------------------------------------------------*/
#define		ADC1_CONVERT_SINGLE			(0x0UL)			/*��ָ��ͨ��ִ��һ��A/D ת��*/
#define		ADC1_CONVERT_CONTINUOUS		(0x1UL<<ADC1_CON_ADCMS_Pos)	/*������ѡ����ͨ����ִ��A/D ת��*/


/*----------------------------------------------------------------------------
 **ADC1 �ⲿ��������ѡ��
-----------------------------------------------------------------------------*/
#define		ADC1_TG_EXT_FALLING			((0x0UL)|ADC1_HWTG_ADCEXTEN_Msk)			/*�ⲿӲ���½��ش���*/
#define		ADC1_TG_EXT_RISING			((0x1UL<<ADC1_HWTG_ADCEXTES_Pos)|ADC1_HWTG_ADCEXTEN_Msk)	/*�ⲿӲ�������ش���*/			
/*----------------------------------------------------------------------------
 **ADC1 EPWM����Դѡ��
-----------------------------------------------------------------------------*/
#define		ADC1_TG_EPWM_CMP0				(0x01UL<<ADC1_HWTG_ADCPTG0EN_Pos)	/*EPWM�����Ƚ���0����*/
#define		ADC1_TG_EPWM_CMP1				(0x01UL<<ADC1_HWTG_ADCPTG1EN_Pos)	/*EPWM�����Ƚ���1����*/
/*----------------------------------------------------------------------------
 **ADC1 ����ͨ��
-----------------------------------------------------------------------------*/
#define		ADC1_CH_0					(0x0UL)			
#define		ADC1_CH_1					(0x1UL)	
#define		ADC1_CH_2					(0x2UL)			
#define		ADC1_CH_3					(0x3UL)			
#define		ADC1_CH_4					(0x4UL)		
#define		ADC1_CH_5					(0x5UL)			
#define		ADC1_CH_6					(0x6UL)	
#define		ADC1_CH_7					(0x7UL)			
#define		ADC1_CH_8					(0x8UL)			
#define		ADC1_CH_9					(0x9UL)		
#define		ADC1_CH_10					(0xAUL)			
#define		ADC1_CH_11					(0xBUL)	
#define		ADC1_CH_12					(0xCUL)			
#define		ADC1_CH_13					(0xDUL)			
#define		ADC1_CH_14					(0xEUL)		
#define		ADC1_CH_15					(0xFUL)			
#define		ADC1_CH_16					(0x10UL)	
#define		ADC1_CH_17					(0x11UL)			
#define		ADC1_CH_18					(0x12UL)			
#define		ADC1_CH_19					(0x13UL)
#define		ADC1_CH_20					(0x14UL)			
#define		ADC1_CH_21					(0x15UL)	
#define		ADC1_CH_22					(0x16UL)			
#define		ADC1_CH_23					(0x17UL)			
#define		ADC1_CH_24					(0x18UL)		
#define		ADC1_CH_25					(0x19UL)			
#define		ADC1_CH_26					(0x1AUL)	
#define		ADC1_CH_27					(0x1BUL)			
#define		ADC1_CH_28					(0x1CUL)			
#define		ADC1_CH_29					(0x1DUL)
#define		ADC1_CH_30					(0x1EUL)

#define		ADC1_CH_0_MSK				(0x1UL)			
#define		ADC1_CH_1_MSK				(0x2UL)	
#define		ADC1_CH_2_MSK				(0x4UL)			
#define		ADC1_CH_3_MSK				(0x8UL)			
#define		ADC1_CH_4_MSK				(0x10UL)		
#define		ADC1_CH_5_MSK				(0x20UL)			
#define		ADC1_CH_6_MSK				(0x40UL)	
#define		ADC1_CH_7_MSK				(0x80UL)			
#define		ADC1_CH_8_MSK				(0x100UL)			
#define		ADC1_CH_9_MSK				(0x200UL)		
#define		ADC1_CH_10_MSK				(0x400UL)			
#define		ADC1_CH_11_MSK				(0x800UL)	
#define		ADC1_CH_12_MSK				(0x1000UL)			
#define		ADC1_CH_13_MSK				(0x2000UL)			
#define		ADC1_CH_14_MSK				(0x4000UL)		
#define		ADC1_CH_15_MSK				(0x8000UL)			
#define		ADC1_CH_16_MSK				(0x10000UL)	
#define		ADC1_CH_17_MSK				(0x20000UL)			
#define		ADC1_CH_18_MSK				(0x40000UL)			
#define		ADC1_CH_19_MSK				(0x80000UL)
#define		ADC1_CH_20_MSK				(0x100000UL)			
#define		ADC1_CH_21_MSK				(0x200000UL)	
#define		ADC1_CH_22_MSK				(0x400000UL)			
#define		ADC1_CH_23_MSK				(0x800000UL)			
#define		ADC1_CH_24_MSK				(0x1000000UL)		
#define		ADC1_CH_25_MSK				(0x2000000UL)			
#define		ADC1_CH_26_MSK				(0x4000000UL)	
#define		ADC1_CH_27_MSK				(0x8000000UL)			
#define		ADC1_CH_28_MSK				(0x10000000UL)			
#define		ADC1_CH_29_MSK				(0x20000000UL)
#define		ADC1_CH_30_MSK				(0x40000000UL)
/*----------------------------------------------------------------------------
 **ADC1 	AN30ѡ���ڲ�ģ��ͨ��
-----------------------------------------------------------------------------*/
#define		ADC1_CH_30_BG			(0x00UL<<ADC0_CON_ADCICHS_Pos)		/*Bandgap 1.2V*/
#define		ADC1_CH_30_OP0O			(0x01UL<<ADC0_CON_ADCICHS_Pos)		/*�˷�0 �����*/
#define		ADC1_CH_30_OP1O			(0x02UL<<ADC0_CON_ADCICHS_Pos)		/*�˷�1 �����*/
#define		ADC1_CH_30_PGA0O		(0x03UL<<ADC0_CON_ADCICHS_Pos)		/*PGA0 �����*/
#define		ADC1_CH_30_PGA1O		(0x04UL<<ADC0_CON_ADCICHS_Pos)		/*PGA1 �����*/
#define		ADC1_CH_30_VREF_VSS		(0x05UL<<ADC0_CON_ADCICHS_Pos)		/*ADC �ο�����*/
#define		ADC1_CH_30_VREF_VDD		(0x06UL<<ADC0_CON_ADCICHS_Pos)		/*ADC �ο�����*/
#define		ADC1_CH_30_VSS			(0x07UL<<ADC0_CON_ADCICHS_Pos)		

/*----------------------------------------------------------------------------
 **ADC1   �Ƚ�
-----------------------------------------------------------------------------*/
#define		ADC1_CMP_LESS_THAN_RESULT		(0x00UL)		/*ADC ���<Ԥ��ֵ*/
#define		ADC1_CMP_NOT_LESS_THAN_RESULT	(0x01UL<<ADC1_CMP0_ADCCMP0COND_Pos)		/*ADC ���>=Ԥ��ֵ*/

#define		ADC1_CMP_SPEED_32M				(0x00UL)		/*֧��FADC �ߴ�32MHz*/
#define		ADC1_CMP_SPEED_4M				(0x01UL<<ADC1_CON_ADCSS_Pos)	/*֧��FADC �ߴ�4MHz*/


/*----------------------------------------------------------------------------
 **ADC1   д����
-----------------------------------------------------------------------------*/
#define		ADC1_LOCK_WRITE_KEY		(0x55UL)




/*****************************************************************************
 ** \brief	ADC1_IS_BUSY
 **			��ȡADC1ת������/���б�־λ
 ** \param [in] none
 ** \return  1��æ   0������/ת�����
 ** \note	 
*****************************************************************************/
#define	ADC1_IS_BUSY()		((ADC1->ADCCON2&ADC1_CON2_ADCST_Msk)? 1:0)



/*****************************************************************************
 ** \brief	ADC1_Go
 **			����ADC1ת��
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
__STATIC_INLINE	void ADC1_Go(void)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCON2 |= ADC1_CON2_ADCST_Msk;
	ADC1->ADCLOCK = 0x00;
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
 ** \brief	ADC1_ConfigRunMode
 **			����ADC����ģʽ
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
void ADC1_ConfigRunMode(uint32_t ConvertMode, uint32_t ClkDiv,uint32_t HoldTime);

/*****************************************************************************
 ** \brief	ADC1_EnableScanChannel
 **			����ADC1ת��ͨ��
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableScanChannel(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC1_DisableScanChannel
 **			�ر�ADC1ת��ͨ��
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableScanChannel(uint32_t ChannelMask);

/*****************************************************************************
 ** \brief	ADC1_SetAN30Channel
 **			����AN30�ڲ�ģ��Դ
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
void ADC1_SetAN30Channel(uint32_t AN30Channel);

/*****************************************************************************
 ** \brief	ADC1_GetResult
 **			��ȡADC1ת�����
 ** \param [in] Channel: ADC1_CH_0 ~ ADC1_CH_30
 ** \return  12 bits Value
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetResult(uint32_t Channel);

/*****************************************************************************
 ** \brief	ADC1_EnableHardwareTrigger
 **			����Ӳ������ADC1ת������
 ** \param [in] TriggerSource: (1)ADC1_TG_EXT_FALLING
 **							(2)ADC1_TG_EXT_RISING
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableHardwareTrigger(uint32_t TriggerSource);
/*****************************************************************************
 ** \brief	ADC1_DisableHardwareTrigger
 **			�ر�Ӳ������ADC1ת������
 ** \param [in] TriggerSource: (1)ADC1_TG_EXT_FALLING
 **							(2)ADC1_TG_EXT_RISING
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableHardwareTrigger(uint32_t TriggerSource);

/*****************************************************************************
 ** \brief	ADC1_EnableCompare
 **			����ADC1�ȽϹ���
 ** \param [in]none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableCompare(void);
/*****************************************************************************
 ** \brief	ADC1_DisableCompare
 **			�ر�ADC1�ȽϹ���
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableCompare(void);
/*****************************************************************************
 ** \brief	ADC1_ConfigCompare
 **			����ADC1�ȽϹ���
 ** \param [in] CmpMode:(1)ADC1_CMP_LESS_THAN_RESULT
 **						 (2)ADC1_CMP_NOT_LESS_THAN_RESULT
 **				 CmpCount: 0x00~0xf  Ԥ��Ƚϴ���
 **				 CmpChannel: ADC1_CH_0 ~ ADC1_CH_30
 **				 CmpData : 12 bit �Ƚ�ֵ
 ** \return  none
 ** \note	���ڲ�����������ADCCMPxMCNT+1��ֵʱ����ADC�Ƚ��¼���
*****************************************************************************/
void ADC1_ConfigCompare( uint32_t CmpMode, uint32_t CmpCount,  
						uint32_t CmpChannel, uint32_t CmpData);

/*****************************************************************************
 ** \brief	ADC1_GetCompareResult
 **			��ȡADC1�Ƚ������
 ** \param [in] Compare : ADC1_CMP0 
 ** \return  1 /0
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareResult(uint32_t Compare);


/*****************************************************************************
 ** \brief	ADC1_Start
 **			����ADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_Start(void);
/*****************************************************************************
 ** \brief	ADC1_Stop
 **			�ر�ADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_Stop(void);

/*****************************************************************************
 ** \brief	ADC1_StartAdjust
 **			����ADC1У׼
 ** \param [in] none
** \return  none
 ** \note	
*****************************************************************************/
void ADC1_StartAdjust(void);

/*****************************************************************************
 ** \brief	ADC1_EnableAdjust
 **			����ADC1����У׼���ݵ�ADCת��
 ** \param [in] none
 ** \return   none
 ** \note	
*****************************************************************************/
void ADC1_EnableAdjust(void);
/*****************************************************************************
 ** \brief	ADC1_DisableAdjust
 **			�ر�ADC1����У׼���ݵ�ADCת��
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableAdjust(void);


/*****************************************************************************
 ** \brief	ADC1_EnableReset
 **			��λADC1
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableReset(void);

/*****************************************************************************
 ** \brief	ADC1_GetConvertErrorFlag
 **			��ȡADC1 ת�������־λ
 ** \param [in] none
 ** \return  1 ��ת�����ִ���	0���޴���
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetConvertErrorFlag(void);
/*****************************************************************************
 ** \brief	ADC1_GetAdjustErrorFlag
 **			��ȡADC1 У׼�����־λ
 ** \param [in] none
 ** \return  1 ��У׼���ִ���	0���޴���
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetAdjustErrorFlag(void);

/*****************************************************************************
 ** \brief	ADC1_ClearConvertErrorFlag
 **			���ADC1 ת�������־λ
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearConvertErrorFlag(void);
/*****************************************************************************
 ** \brief	ADC1_ClearAdjustErrorFlag
 **			���ADC1 У׼�����־λ
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearAdjustErrorFlag(void);

/*****************************************************************************
 ** \brief	ADC1_EnableCompareInt
 **			����ADC1�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableCompareInt(void);
/*****************************************************************************
 ** \brief	ADC1_DisableCompareInt
 **			�ر�ADC1�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableCompareInt(void);
/*****************************************************************************
 ** \brief	ADC1_GetCompareIntFlag
 **			��ȡADC1�Ƚ��ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] none
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareIntFlag(void);
/*****************************************************************************
 ** \brief	ADC1_ClearCompareIntFlag
 **			���ADC1�Ƚ��жϱ�־λ
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearCompareIntFlag(void);

/*****************************************************************************
 ** \brief	ADC1_EnableChannelInt
 **			����ADC1ͨ��n�ж�
 ** \param [in]ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_EnableChannelInt(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC1_DisableChannelInt
 **			�ر�ADC1ͨ��n�ж�
 ** \param [in] ChannelMask: ADC1_CH_0_MSK ~ ADC1_CH_30_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_DisableChannelInt(uint32_t ChannelMask);
/*****************************************************************************
 ** \brief	ADC1_GetChannelIntFlag
 **			��ȡADC1ͨ��n�ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] Channel:ADC1_CH_0 ~ ADC1_CH_30
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetChannelIntFlag(uint32_t Channel);
/*****************************************************************************
 ** \brief	ADC1_ClearChannelIntFlag
 **			���ADC1ͨ��n�жϱ�־λ
 ** \param [in] Channel:ADC1_CH_0 ~ ADC1_CH_30
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC1_ClearChannelIntFlag(uint32_t Channel);


void ADC1_EnableEPWMCmp0TiggerChannel(uint32_t ChannelMask);


#ifdef __cplusplus
}
#endif

#endif /* __ADC1_H_ */

