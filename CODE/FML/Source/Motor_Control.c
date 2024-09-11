
/*----------------------------------include-----------------------------------*/
#include "Motor_Control.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
Trig_Components Vector_Components;

int16_t cnt = S16_MIN;//�������Ա���

//FOC���
//Trig_Components Vector_Components;
Curr_Components Stat_Curr_a_b;            
Curr_Components Stat_Curr_alfa_beta;       
Curr_Components Stat_Curr_q_d;             
Curr_Components Stat_Curr_q_d_ref_ref;   //�������ĸ���ֵ�����ڵ�����Id,Iq��ǰ���������Ƶĸ���ֵ
Volt_Components Stat_Volt_q_d;             
Volt_Components Stat_Volt_alfa_beta; 
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void FOC_Model(void)
{
    //��������
    Stat_Volt_q_d.qV_Component1 = 0;
    Stat_Volt_q_d.qV_Component2 = 3000;

    cnt += 500;
    if(cnt > S16_MAX)
    {
        cnt = S16_MIN;
    }

    Stat_Volt_alfa_beta = MCM_Rev_Park(Stat_Volt_q_d ,cnt);
    SVPWM_SetPhaseVoltage(Stat_Volt_alfa_beta);
}
/*------------------------------------test------------------------------------*/
