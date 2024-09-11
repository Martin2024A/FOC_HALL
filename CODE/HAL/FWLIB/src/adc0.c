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
/** \file adc0.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "adc0.h"
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
 ** \brief	ADC0_ConfigRunMode
 **			����ADC0����ģʽ
 ** \param [in] 				
 **				ChannelSwitch: (1)ADC0_CONVERT_SINGLE
 **							   (2)ADC0_CONVERT_CONTINUOUS
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
void ADC0_ConfigRunMode(uint32_t ChannelSwitch, uint32_t ClkDiv)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCON &= ~(ADC0_CON_ADCDIV_Msk | ADC0_CON_ADcms_Msk);
	ADC0->ADCCON |=  ClkDiv | ChannelSwitch;
	ADC0->ADCLOCK = 0x00;	
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
void ADC0_SetAN30Channel(uint32_t AN30Channel)
{
	ADC0->ADCLOCK = ADC1_LOCK_WRITE_KEY;	
	ADC0->ADCCON &= ~(ADC1_CON_ADCICHS_Msk);
	ADC0->ADCCON |= AN30Channel;		
	ADC0->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC0_EnableChannel
 **			����ADC0ת��ͨ��
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableChannel(uint32_t ChannelMask)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;		
	ADC0->ADCSCAN |= ChannelMask;
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_DisableChannel
 **			�ر�ADC0ת��ͨ��
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableChannel(uint32_t ChannelMask)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;		
	ADC0->ADCSCAN &= ~(ChannelMask);
	ADC0->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC0_SelSoftwareSwitchChannel
 **			ѡ������л�ת����ͨ��
 ** \param [in] Channel: ADC0_CH_0 ~ ADC0_CH_19
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_SelSoftwareSwitchChannel(uint32_t Channel)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCON2 = Channel;
	ADC0->ADCSCAN = (0x1<<Channel);
	ADC0->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC0_GetResult
 **			��ȡADC0ת�����
 ** \param [in] Channel: ADC0_CH_0 ~ ADC0_CH_30
 ** \return  12 bits Value
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetResult(uint32_t Channel)
{
	return(ADC0->ADCDATA[Channel]);
}

/*****************************************************************************
 ** \brief	ADC0_EnableHardwareTrigger
 **			����Ӳ������ADC0ת������
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
void ADC0_EnableHardwareTrigger(uint32_t TriggerSource)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	switch(TriggerSource)
	{
		case ADC0_TG_EXT_FALLING:
		case ADC0_TG_EXT_RISING:
			ADC0->ADCHWTG |= TriggerSource;
			break;
		case ADC0_TG_INTNEL_ADC0:
		case ADC0_TG_INTNEL_ADCB:
		case ADC0_TG_INTNEL_ACMP0:
		case ADC0_TG_INTNEL_ACMP1:
		case ADC0_TG_INTNEL_TMR0:
		case ADC0_TG_INTNEL_TMR1:		
			ADC0->ADCHWTG &= ~(ADC0_HWTG_ADCINTTGSS_Msk);
			ADC0->ADCHWTG |= TriggerSource;
			break;			
		default:
			break;
	}	
	ADC0->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC0_DisableHardwareTrigger
 **			�ر�Ӳ������ADC0ת������
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
void ADC0_DisableHardwareTrigger(uint32_t TriggerSource)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	switch(TriggerSource)
	{
		case ADC0_TG_EXT_FALLING:
		case ADC0_TG_EXT_RISING:
			ADC0->ADCHWTG &= ~(ADC0_HWTG_ADCEXT0TEN_Msk);
			break;
		case ADC0_TG_INTNEL_ADC0:
		case ADC0_TG_INTNEL_ADCB:
		case ADC0_TG_INTNEL_ACMP0:
		case ADC0_TG_INTNEL_ACMP1:
		case ADC0_TG_INTNEL_TMR0:
		case ADC0_TG_INTNEL_TMR1:		
			ADC0->ADCHWTG &= ~(ADC0_HWTG_ADCINTTGEN_Msk);
			break;			
		default:
			break;
	}	
	ADC0->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC0_EnableCompare
 **			����ADC0�ȽϹ���
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableCompare(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCMP0 |= ADC0_CMP0_CMP0EN_Msk;
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_DisableCompare
 **			�ر�ADC0�ȽϹ���
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableCompare(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCMP0 &= ~(ADC0_CMP0_CMP0EN_Msk);
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_ConfigCompare
 **			����ADC0�ȽϹ���
 ** \param [in] CmpMode:(1)ADC0_CMP_LESS_THAN_RESULT
 **						(2)ADC0_CMP_NOT_LESS_THAN_RESULT
 **				 CmpCount: 0x00~0xf  Ԥ��Ƚϴ���
 **				 CmpChannel: ADC0_CH_0 ~ ADC0_CH_19
 **				 CmpData : 12 bit �Ƚ�ֵ
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ConfigCompare(uint32_t CmpMode, uint32_t CmpCount,  
						uint32_t CmpChannel, uint32_t CmpData)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;
	ADC0->ADCCMP0 &= ~(ADC0_CMP0_CMP0COND_Msk|ADC0_CMP0_CMP0MCNT_Msk|
					ADC0_CMP0_CMP0CHS_Msk| ADC0_CMP0_CMP0DATA_Msk);
	ADC0->ADCCMP0 |= CmpMode | ((0xf & CmpCount)<<ADC0_CMP0_CMP0MCNT_Pos) | 
				((CmpChannel & 0x1f)<<ADC0_CMP0_CMP0CHS_Pos) | (0xfff &CmpData);
	ADC0->ADCLOCK = 0x00;		
}

/*****************************************************************************
 ** \brief	ADC0_GetCompareResult
 **			��ȡADC0�Ƚ������
 ** \param [in] none
 ** \return  1 /0
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetCompareResult(void)
{
	return((ADC0->ADCCMP0 & ADC0_CMP0_CMP0O_Msk)? 1:0);
}

/*****************************************************************************
 ** \brief	ADC0_EnableCompareInt
 **			����ADC0�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableCompareInt(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCIMSC |= ADC0_IMSC_IMSC31_Msk;
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_DisableCompareInt
 **			�ر�ADC0�Ƚ��ж�
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableCompareInt(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCIMSC &= ~(ADC0_IMSC_IMSC31_Msk);
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_GetCompareIntFlag
 **			��ȡADC0�Ƚ��ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] none
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetCompareIntFlag(void)
{
	return((ADC0->ADCMIS & ADC0_MIS_MIS31_Msk)? 1:0);
}
/*****************************************************************************
 ** \brief	ADC0_ClearCompareIntFlag
 **			���ADC0�Ƚ��жϱ�־λ
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ClearCompareIntFlag(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCICLR |= (ADC0_ICLR_ICLR31_Msk);
	ADC0->ADCLOCK = 0x00;	
}

/*****************************************************************************
 ** \brief	ADC0_EnableChannelInt
 **			����ADC0ͨ��n�ж�
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_EnableChannelInt(uint32_t ChannelMask)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCIMSC |= ChannelMask ;
	ADC0->ADCLOCK = 0x00;	
}
/*****************************************************************************
 ** \brief	ADC0_DisableChannelInt
 **			�ر�ADC0ͨ��n�ж�
 ** \param [in] ChannelMask: ADC0_CH_0_MSK ~ ADC0_CH_19_MSK
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_DisableChannelInt(uint32_t ChannelMask)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCIMSC &= ~(ChannelMask);
	ADC0->ADCLOCK = 0x00;
}
/*****************************************************************************
 ** \brief	ADC0_GetChannelIntFlag
 **			��ȡADC0ͨ��n�ж�ʹ�ܲ��Ҳ����жϱ�־λ
 ** \param [in] Channel:ADC0_CH_0 ~ ADC0_CH_19
 ** \return  1:�ж�ʹ�ܲ��Ҳ����ж� 0�����ж�
 ** \note	
*****************************************************************************/
uint32_t ADC0_GetChannelIntFlag(uint32_t Channel)
{
	return((ADC0->ADCMIS & (0x1UL<<Channel))? 1:0);	
}
/*****************************************************************************
 ** \brief	ADC0_ClearChannelIntFlag
 **			���ADC0ͨ��n�жϱ�־λ
 ** \param [in] Channel:ADC0_CH_0 ~ ADC0_CH_19
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_ClearChannelIntFlag(uint32_t Channel)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCICLR |= (0x01UL<< Channel);
	ADC0->ADCLOCK = 0x00;		
}
/*****************************************************************************
 ** \brief	ADC0_Start
 **			����ADC0
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_Start(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCCON |= ADC0_CON_ADCEN_Msk;
	ADC0->ADCLOCK = 0x00;			
}
/*****************************************************************************
 ** \brief	ADC0_Stop
 **			�ر�ADC0
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void ADC0_Stop(void)
{
	ADC0->ADCLOCK = ADC0_LOCK_WRITE_KEY;	
	ADC0->ADCICLR &= ~(ADC0_CON_ADCEN_Msk);
	ADC0->ADCLOCK = 0x00;		
}

