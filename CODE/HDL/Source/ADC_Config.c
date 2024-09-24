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
	(1)设置ADC1时钟
	*/
    SYS_EnablePeripheralClk(SYS_CLK_ADC1_MSK);
	ADC1_ConfigRunMode(ADC1_CONVERT_CONTINUOUS,ADC1_CLK_DIV_8,ADC1_HOLD_10P5_CLK);			/*使能单通道转换*/

	/*
	(2)设置ADC1通道使能
	*/	
	ADC1_EnableScanChannel(ADC1_CH_8_MSK | ADC1_CH_30_MSK);						/*触发的通道选择AN13 */	
	SYS_SET_IOCFG(IOP13CFG,SYS_IOCFG_P13_AN8);					/*关闭P21的数字功能*/
    ADC1_SetAN30Channel(ADC1_CH_30_VREF_VDD);

	/*
	(3)设置ADC1硬件触发
	*/	
	 ADC1_EnableHardwareTrigger(ADC1_TG_EPWM_CMP0);
	 ADC1_EnableEPWMCmp0TiggerChannel(ADC1_CH_30_MSK);

	/*
	(4)设置ADC1中断
	*/	
	ADC1_EnableChannelInt(ADC1_CH_30_MSK);						/*开AN30转换中断*/	

	/*
	(6)开启ADC1
	*/	
	ADC1_Start();

	// /*
	// (7)开启ADC1校准
	// */		
	ADC1_StartAdjust();
	// /*
	// (8)使用ADC1校准值的ADC转换
	// */	
	ADC1_EnableAdjust();
}
/*------------------------------------test------------------------------------*/
