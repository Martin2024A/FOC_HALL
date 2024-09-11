/**************************************************************************//**
 * @file     system_CMS32M55xx.h
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Header File
 *           for the CMS CMS32M55xx Series
 * @version  V1.00
 * @date     06. November 2019
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

#ifndef __SYSTEM_CMS32M55XX_H
#define __SYSTEM_CMS32M55XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
/*----------------------------------------------------------------------------
  Define SYSCLK
 *----------------------------------------------------------------------------*/

extern uint32_t SystemCoreClock;      /*!< System Clock Frequency (Core Clock)  */
extern uint32_t SystemAPBClock;       /*!< System APB Clock Frequency (APB Clock)*/
extern uint32_t CyclesPerUs;          /* Cycles per micro second */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);


/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

/* Enable Interrupt */
#define __EI    __enable_irq()
/* Disable Interrupt */
#define __DI  	__disable_irq()

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_CMS32M55xx_H */
