
#ifndef MAIN_H 
#define MAIN_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "CMS32M55xx.h"
#include "UART_Config.h"
#include "Motor_Control.h"
#include "CCP_Config.h"
#include "Hall_Commutation.h"

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void SoftwareInit(void);
void HardwareInit(void);
void NVIC_Init(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* MAIN_H */
