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
void ADC1_ConfigRunMode(uint32_t ConvertMode, uint32_t ClkDiv,uint32_t HoldTime)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;
	ADC1->ADCCON &= ~(ADC1_CON_ADCMS_Msk|ADC1_CON_ADCDIV_Msk|ADC1_CON_ADCSHT_Msk);
	ADC1->ADCCON |= ConvertMode |  ClkDiv | HoldTime;	
	ADC1->ADCLOCK = 0x00;
}

/*****************************************************************************
 ** \brief	ADC1_EnableScanChannel
 **			����ADC1ת��ͨ��
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
 **			�ر�ADC1ת��ͨ��
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
void ADC1_SetAN30Channel(uint32_t AN30Channel)
{
	ADC1->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC1->ADCCON &= ~(ADC1_CON_ADCICHS_Msk);
	ADC1->ADCCON |= AN30Channel;		
	ADC1->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC1_GetResult
 **			��ȡADC1ת�����
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
 **			����Ӳ������ADC1ת������
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
 **			ʹ�� EPWM �Ƚ���0 ������ADC1ת��ͨ��
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
 **			�ر�Ӳ������ADC1ת������
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
 **			����ADC1�ȽϹ���
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
 **			�ر�ADC1�ȽϹ���
 ** \param [in] Compare : ADC1_CMP0 ��ADC1_CMP1
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
 **			����ADC1�ȽϹ���
 ** \param [in]  CmpMode:(1)ADC1_CMP_LESS_THAN_RESULT
 **						(2)ADC1_CMP_NOT_LESS_THAN_RESULT
 **				 CmpCount: 0x00~0xf  Ԥ��Ƚϴ���
 **				 CmpChannel: ADC1_CH_0 ~ ADC1_CH_30
 **				 CmpData : 12 bit �Ƚ�ֵ
 ** \return  none
 ** \note	���ڲ�����������ADCCMPxMCNT+1��ֵʱ����ADC�Ƚ��¼���
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
 **			��ȡADC1�Ƚ������
 ** \param [in] Compare : ADC1_CMP0 ��ADC1_CMP1
 ** \return  1 /0
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareResult(uint32_t Compare)
{
	return((ADC1->ADCCMP0 & ADC1_CMP_ADCCMPO_Msk)? 1:0);
}


/*****************************************************************************
 ** \brief	ADC1_Start
 **			����ADC1
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
 **			�ر�ADC1
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
 **			����ADC1У׼
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
 **			����ADC1����У׼���ݵ�ADCת��
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
 **			�ر�ADC1����У׼���ݵ�ADCת��
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
 **			��λADC1
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
 **			��ȡADC1 ת�������־λ
 ** \param [in] none
 ** \return  1 ��ת�����ִ���	0���޴���
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetConvertErrorFlag(void)
{
	return((ADC1->ADCCON & ADC1_CON_ADCCONVER_Msk)? 1:0);	
}
/*****************************************************************************
 ** \brief	ADC1_GetAdjustErrorFlag
 **			��ȡADC1 У׼�����־λ
 ** \param [in] none
 ** \return  1 ��У׼���ִ���	0���޴���
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetAdjustErrorFlag(void)
{
	return((ADC1->ADCCON & ADC1_CON_ADCCALERR_Msk)? 1:0);	
}

/*****************************************************************************
 ** \brief	ADC1_ClearConvertErrorFlag
 **			���ADC1 ת�������־λ
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
 **			���ADC1 У׼�����־λ
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
 **			����ADC1�Ƚ��ж�
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
 **			�ر�ADC1�Ƚ��ж�
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
 **			��ȡADC1�Ƚ��ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] none
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetCompareIntFlag(void)
{
	return((ADC1->ADCMIS & ADC1_MIS_MIS31_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	ADC1_ClearCompareIntFlag
 **			���ADC1�Ƚ��жϱ�־λ
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
 **			����ADC1ͨ��n�ж�
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
 **			�ر�ADC1ͨ��n�ж�
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
 **			��ȡADC1ͨ��n�ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] Channel:ADC1_CH_0 ~ ADC1_CH_30
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC1_GetChannelIntFlag(uint32_t Channel)
{
	return((ADC1->ADCMIS & (0x1UL<<Channel))? 1:0);	
}
/*****************************************************************************
 ** \brief	ADC1_ClearChannelIntFlag
 **			���ADC1ͨ��n�жϱ�־λ
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
