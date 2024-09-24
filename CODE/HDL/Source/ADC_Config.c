/*----------------------------------include-----------------------------------*/
#include "ADC_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void ADC_Init(void)
{
	/*
	(1)����ADC1ʱ��
	*/
    SYS_EnablePeripheralClk(SYS_CLK_ADC1_MSK);
	ADC1_ConfigRunMode(ADC1_CONVERT_CONTINUOUS,ADC1_CLK_DIV_8,ADC1_HOLD_10P5_CLK);			/*ʹ�ܵ�ͨ��ת��*/

	/*
	(2)����ADC1ͨ��ʹ��
	*/	
	ADC1_EnableScanChannel(ADC1_CH_8_MSK | ADC1_CH_30_MSK);						/*������ͨ��ѡ��AN13 */	
	SYS_SET_IOCFG(IOP13CFG,SYS_IOCFG_P13_AN8);					/*�ر�P21�����ֹ���*/
    ADC1_SetAN30Channel(ADC1_CH_30_VREF_VDD);

	/*
	(3)����ADC1Ӳ������
	*/	
	 ADC1_EnableHardwareTrigger(ADC1_TG_EPWM_CMP0);
	 ADC1_EnableEPWMCmp0TiggerChannel(ADC1_CH_30_MSK);

	/*
	(4)����ADC1�ж�
	*/	
	ADC1_EnableChannelInt(ADC1_CH_30_MSK);						/*��AN30ת���ж�*/	

	/*
	(6)����ADC1
	*/	
	ADC1_Start();

	// /*
	// (7)����ADC1У׼
	// */		
	ADC1_StartAdjust();
	// /*
	// (8)ʹ��ADC1У׼ֵ��ADCת��
	// */	
	ADC1_EnableAdjust();
}
/*------------------------------------test------------------------------------*/
