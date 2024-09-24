
/*----------------------------------include-----------------------------------*/
#include "Motor_CurrentScan.h"
/*-----------------------------------macro------------------------------------*/
//α����
/*
FOC�����ת�����ġ���EPWM
��������1���ڣ�
    Hall��0���»�ȡ��Ƕȣ����С��30��
    �趨Iq��Id
    PID����
    ��Clark�任��I����I��
    SVPWM���� EPWMռ�ձȣ�ʱ�䣩
    ����ռ�ձȼ��������Ͳ���
    ���õ�һ�β�����
���У���2���ڣ�
    ADC��һ�β�������¼ADCֵ�����õڶ��β�����
    ADC�ڶ��β�����
        ��¼ADCֵ���������
        ��ȡHall��Ƕ�
        clark�仯
        park�仯
        PID
        ��Clark
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
