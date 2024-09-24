
/*----------------------------------include-----------------------------------*/
#include "Motor_CurrentScan.h"
/*-----------------------------------macro------------------------------------*/
//伪代码
/*
FOC如何运转起来的——EPWM
启动：（1周期）
    Hall在0速下获取电角度（误差小于30）
    设定Iq、Id
    PID计算
    逆Clark变换得Iα、Iβ
    SVPWM计算 EPWM占空比（时间）
    根据占空比计算采样点和补偿
    设置第一次采样点
运行：（2周期）
    ADC第一次采样：记录ADC值，设置第二次采样点
    ADC第二次采样：
        记录ADC值，计算电流
        获取Hall电角度
        clark变化
        park变化
        PID
        逆Clark
        SVPWM
*/
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
volatile uint8_t  CurrentScan_Flag =0;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void ADC_CurrentScan(void)
{
    Curr_Components Curr_Output;
    int32_t current_temp_a,current_temp_b,current_temp_c;
    if(ADC1_GetChannelIntFlag(ADC1_CH_8))
	{
        if(CurrentScan_Flag == 0)
        {
            switch(bSector)
            {
                case 1:
                case 2:
                    current_temp_c = -ADC1_GetResult(ADC1_CH_8);//-Ic
                    break;
                case 3:
                case 4:
                    current_temp_a =  -ADC1_GetResult(ADC1_CH_8);//-Ia
                    break;
                case 5:
                case 6:
                    current_temp_b = -ADC1_GetResult(ADC1_CH_8);//-Ib
                    break;
            }
            EPWM_ConfigCompareTriger(EPWM_CMPTG_0,EPWM_CMPTG_FALLING,EPWM_CMPTG_EPWM0,100);
            CurrentScan_Flag = 1;
        }
        else if(CurrentScan_Flag == 1)
        {
            switch(bSector)
            {
                case 1:
                case 6:
                    current_temp_a = ADC1_GetResult(ADC1_CH_8);//Ia
                    break;
                case 2:
                case 3:
                    current_temp_b = ADC1_GetResult(ADC1_CH_8);//Ib
                    break;
                
                case 4:
                case 5:
                    current_temp_c =  ADC1_GetResult(ADC1_CH_8);//Ic
                    break;
            }

            switch(bSector)
            {
                case 1:
                    Curr_Output.qI_Component1 = current_temp_a;
                    Curr_Output.qI_Component2 = -current_temp_c-current_temp_a;
                    break;
                case 2:
                    Curr_Output.qI_Component1 = -current_temp_c-current_temp_b;
                    Curr_Output.qI_Component2 = current_temp_b;

            }
        }
    }
}


        




/*------------------------------------test------------------------------------*/
