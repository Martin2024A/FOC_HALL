;/*****************************************************************************
; * @file:    startup_CMS32M55xx.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File for the 
; *           CMSARM CMS32M55xx Series 
; * @version: V1.0
; * @date     31-March-2015
; *
; * @note
; * Copyright (C) 2010-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     GPIO0_IRQHandler          ; GPIO P0 Interrupt			;0
                DCD     GPIO1_IRQHandler          ; GPIO P1 Interrupt			;1
                DCD     GPIO2_IRQHandler          ; GPIO P2 Interrupt			;2
                DCD     GPIO3_IRQHandler          ; GPIO P3 Interrupt			;3
                DCD     GPIO4_IRQHandler          ; GPIO P4 Interrupt			;4
                DCD     Reserved_IRQHandler       ; Reserved          			;5					
                DCD     CCP_IRQHandler            ; Capture/PWM					;6
                DCD     ADC0_IRQHandler           ; A/D Converter				;7
                DCD     Reserved_IRQHandler       ; Reserved                    ;8
                DCD     WWDT_IRQHandler           ; WWDT                 		;9
				DCD     EPWM_IRQHandler           ; EPWM                		;10
                DCD     Reserved_IRQHandler       ; Reserved                 	;11
                DCD     ADC1_IRQHandler           ; ADC1         			    ;12
                DCD     ACMP_IRQHandler           ; ACMP           			    ;13
                DCD     Reserved_IRQHandler       ; Reserved           			;14
                DCD     UART0_IRQHandler          ; UART0                 		;15
                DCD     UART1_IRQHandler          ; UART1                		;16
                DCD     Reserved_IRQHandler       ; Reserved                	;17
                DCD     Reserved_IRQHandler       ; Reserved              		;18
                DCD     TIMER0_IRQHandler         ; Timer0                   	;19
                DCD     TIMER1_IRQHandler         ; Timer1             			;20
                DCD     Reserved_IRQHandler       ; Reserved              		;21
                DCD     Reserved_IRQHandler       ; Reserved                	;22
                DCD     WDT_IRQHandler            ; Watchdog timer        		;23
                DCD     I2C0_IRQHandler           ; I2C0                   		;24
                DCD     Reserved_IRQHandler       ; Reserved             		;25
                DCD     SSP0_IRQHandler           ; SSP0                     	;26
                DCD     Reserved_IRQHandler       ; Reserved               		;27
                DCD     Reserved_IRQHandler       ; Reserved           			;28
                DCD     Reserved_IRQHandler       ; Reserved                 	;29
                DCD     Reserved_IRQHandler       ; Reserved             		;30
                DCD     SYS_CHK_IRQHandler        ; SYS_CHK	          			;31


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
				
				LDR     R0, =SystemInit
				BLX     R0
				LDR     R0, =__main
				BX      R0
				ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
Reserved_IRQHandler PROC
                EXPORT  Reserved_IRQHandler       [WEAK]
                B       .
                ENDP


Default_Handler PROC
                EXPORT  GPIO0_IRQHandler          [WEAK]		
                EXPORT  GPIO1_IRQHandler          [WEAK]		
                EXPORT  GPIO2_IRQHandler          [WEAK]
                EXPORT  GPIO3_IRQHandler          [WEAK]
                EXPORT  GPIO4_IRQHandler          [WEAK]
                EXPORT  CCP_IRQHandler            [WEAK]
                EXPORT  ADC0_IRQHandler           [WEAK]
                EXPORT  WWDT_IRQHandler           [WEAK]
                EXPORT  EPWM_IRQHandler           [WEAK]
                EXPORT  ADC1_IRQHandler           [WEAK]
                EXPORT  ACMP_IRQHandler           [WEAK]					
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT	SYS_CHK_IRQHandler	      [WEAK]
GPIO0_IRQHandler  
GPIO1_IRQHandler  
GPIO2_IRQHandler  
GPIO3_IRQHandler  
GPIO4_IRQHandler  
CCP_IRQHandler     
ADC0_IRQHandler   
WWDT_IRQHandler   
EPWM_IRQHandler   
ADC1_IRQHandler   
ACMP_IRQHandler   
UART0_IRQHandler  
UART1_IRQHandler  
TIMER0_IRQHandler 
TIMER1_IRQHandler 
WDT_IRQHandler    
I2C0_IRQHandler   
SSP0_IRQHandler   
SYS_CHK_IRQHandler

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
