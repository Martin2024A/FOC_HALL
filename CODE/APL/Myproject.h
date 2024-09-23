#ifndef MYPROJECT_H 
#define MYPROJECT_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "CMS32M55xx.h"

#include "System_Config.h"
#include "UART_Config.h"
#include "ADC_Config.h"
#include "EPWM_Config.h"
#include "CCP_Config.h"
#include "TIM_Config.h"

#include "UART_Process.h"
#include "Motor_math.h"
#include "Motor_type.h"
#include "Motor_SVPWM.h"
#include "Hall_Commutation.h"
#include "Motor_Control.h"

#include "main.h"

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* MYPROJECT_H */
