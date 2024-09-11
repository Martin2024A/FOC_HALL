
#ifndef MOTOR_SVPWM_H 
#define MOTOR_SVPWM_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "Motor_type.h"
#include "EPWM_Config.h"
/*-----------------------------------macro------------------------------------*/
#define CKTIM             48000000                //定时器时钟频率
#define PWM_PRSC          0                       //不分频
#define PWM_FREQ          5000                   //目标PWM频率
#define PWM_MODE          EPWM_COUNT_UP_DOWN      //上下计数（中心对齐）模式
#define PWM_PERIOD_CYCLE  CKTIM/(PWM_FREQ*(PWM_PRSC+1))
#define PWM_ARR           PWM_PERIOD_CYCLE/2

#define T_SQRT3           ((PWM_PERIOD_CYCLE * SQRT3_FACTOR) /16384u)

#define REP_RATE    1                       //电流环刷新频率为(REP_RATE+1)/(2*PWM_FREQ)
#define DEADTIME_NS 1000                    //死区时间ns
#define DEADTIME    CKTIM/1000000/2*DEADTIME_NS/1000
#define POLE_PAIR_NUM 4                     //极对数
#define ICx_FILTER  8
#define PERIOD      PWM_PERIOD


#define SECTOR_1  0u
#define SECTOR_2  1u
#define SECTOR_3  2u
#define SECTOR_4  3u
#define SECTOR_5  4u
#define SECTOR_6  5u

#define TW_AFTER ((uint16_t)(((DEADTIME_NS+MAX_TNTR_NS)*48uL)/1000ul))
#define TW_BEFORE (((uint16_t)(((((uint16_t)(SAMPLING_TIME_NS)))*48uL)/1000ul))+1)
#define TNOISE_NS 1550     //2.55usec
#define TRISE_NS 1550     //2.55usec
#define SAMPLING_TIME_NS   700  //700ns
#define SAMPLING_TIME (uint16_t)(((uint16_t)(SAMPLING_TIME_NS) * 48uL)/1000uL) 
#define TNOISE (uint16_t)((((uint16_t)(TNOISE_NS)) * 48uL)/1000uL)
#define TRISE (uint16_t)((((uint16_t)(TRISE_NS)) * 48uL)/1000uL)
#define TDEAD (uint16_t)((DEADTIME_NS * 48uL)/1000uL)

#if (TNOISE_NS > TRISE_NS)
  #define MAX_TNTR_NS TNOISE_NS
#else
  #define MAX_TNTR_NS TRISE_NS
#endif

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/


/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void SVPWM_SetPhaseVoltage(Volt_Components Valfa_beta);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* MOTOR_SVPWM_H */
