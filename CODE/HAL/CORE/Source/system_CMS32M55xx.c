/**************************************************************************//**
 * @file     system_CMS32M55xx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 *           for the CMS CMS32M55xx Series
 * @version  V2.10
 * @date     20. July 2011
 *
 * @note
 * Copyright (C) 2010-2011 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include <stdint.h>
#include "CMS32M55xx.h"
#include "system_CMS32M55xx.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define HSI_64M_VAL 64000000
#define HSI_48M_VAL 48000000
#define RC_40K_VAL  40000

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()    */
uint32_t SystemCoreClock = HSI_64M_VAL;  /*!< System Clock Frequency (Core Clock)*/
uint32_t SystemAPBClock  = HSI_64M_VAL;  /*!< System APB Clock Frequency (APB Clock)*/
uint32_t CyclesPerUs = ( HSI_64M_VAL / 1000000 ); /* Cycles per micro second */


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate ( void )          /* Get Core Clock Frequency      */
{
	/* ToDo: add code to calculate the system frequency based upon the current
	         register settings.
	         This function can be used to retrieve the system core clock frequeny
	         after user changed register sittings.                                */

	switch ( SYSCON->CLKSEL )
	{
	case 0:
		if( ( SYSCON->CLKCON & 0x03 ) == 0x03 ) //48M
		{
			SystemCoreClock = HSI_48M_VAL;
		}
		else      //64M
		{
			SystemCoreClock = HSI_64M_VAL;
		}

		break;

	case 1:

		break;

	case 2:   //40K
		SystemCoreClock = RC_40K_VAL;
		break;
	}

	if( SYSCON->AHBCKDIV != 0 )
		SystemCoreClock   /= ( 2 * SYSCON->AHBCKDIV );

	if( SYSCON->APBCKDIV != 0 )
		SystemAPBClock    /= ( 2 * SYSCON->APBCKDIV );
	else
		SystemAPBClock = SystemCoreClock;

	CyclesPerUs = SystemCoreClock / 1000000;
}


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit ( void )
{
	/* ToDo: add code to initialize the system
	         do not use global variables because this function is called before
	         reaching pre-main. RW section maybe overwritten afterwards.          */
	SystemCoreClockUpdate ();
}
