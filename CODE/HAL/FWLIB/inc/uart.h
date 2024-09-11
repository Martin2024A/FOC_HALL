/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/*****************************************************************************/
/** \file uart.h
**
** History:
** 
*****************************************************************************/
#ifndef __UART_H_
#define __UART_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "CMS32M55xx.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/
/*----------------------------------------------------------------------------
 **UART �ֳ�
-----------------------------------------------------------------------------*/
#define		UART_WLS_5			(0x00UL)		/*5λ�ֳ�*/
#define		UART_WLS_6			(0x01UL)		/*6λ�ֳ�*/
#define		UART_WLS_7			(0x02UL)		/*7λ�ֳ�*/		
#define		UART_WLS_8			(0x03UL)		/*8λ�ֳ�*/
/*----------------------------------------------------------------------------
 **UART ֹͣλ
-----------------------------------------------------------------------------*/
#define		UART_STOP_BIT_1			(0x00UL)		/*1λֹͣλ*/
#define		UART_STOP_BIT_2			(0x01UL<<UART_LCR_SBS_Pos)		/*2λֹͣλ*/
/*----------------------------------------------------------------------------
 **UART ��żУ��
-----------------------------------------------------------------------------*/
#define		UART_PARITY_NONE		(0x00UL)		/*����żУ��*/
#define		UART_PARITY_ODD			(0x00UL|(0x1<<UART_LCR_PEN_Pos))	/*��żУ��*/
#define		UART_PARITY_EVEN		((0x01UL<<UART_LCR_PSEL_Pos)|(0x1<<UART_LCR_PEN_Pos))	/*żżУ��*/
#define		UART_PARITY_FORCE_1		((0x02UL<<UART_LCR_PSEL_Pos)|(0x1<<UART_LCR_PEN_Pos))		/*У��λǿ��Ϊ1*/
#define		UART_PARITY_FORCE_0		((0x03UL<<UART_LCR_PSEL_Pos)|(0x1<<UART_LCR_PEN_Pos))		/*У��λǿ��Ϊ0*/

/*----------------------------------------------------------------------------
 **UART FIFO Level
-----------------------------------------------------------------------------*/
#define 	FIFO_L0_1BYTE			(0x0UL)		
#define 	FIFO_L1_4BYTE			(0x1UL)		
#define 	FIFO_L2_8BYTE			(0x2UL)		
#define 	FIFO_L3_14BYTE			(0x3UL)		
/*----------------------------------------------------------------------------
 **UART FIFO Reset 
-----------------------------------------------------------------------------*/
#define 	FIFO_RST_EN				(0x1UL)			
#define 	FIFO_RST_DIS			(0x0UL)		

/*----------------------------------------------------------------------------
 **UART XON XOFF
-----------------------------------------------------------------------------*/
#define		UART_USE_XON1_XOFF1		(0x02)
#define		UART_USE_XON2_XOFF2		(0x01)
#define		UART_USE_BOTH_XON_XOFF		(0x03)		/*XON1&XON2,XOFF1&XOFF2*/

							
/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/

/*****************************************************************************
 ** \brief	UART_ConfigRunMode
 **			�����첽��������ģʽ
 ** \param [in] uart: UART0��UART1
 **				Baudrate:������
 **				WordLength:(1)UART_WLS_5
 **							(2)UART_WLS_6
 **							(3)UART_WLS_7
 **							(4)UART_WLS_8
 **				Parity:	(1)UART_PARITY_NONE
 **						(2)UART_PARITY_ODD
 **						(3)UART_PARITY_EVEN
 **						(4)UART_PARITY_FORCE_1
 **					 	(5)UART_PARITY_FORCE_0
 **				StopBit:(1)UART_STOP_BIT_1
 **						(2)UART_STOP_BIT_2
 ** \return  none
 ** \note	
*****************************************************************************/
void UART_ConfigRunMode(UART0_Type* uart,uint32_t Baudrate,uint32_t WordLength, 
						uint32_t Parity, uint32_t StopBit);

/*****************************************************************************
 ** \brief	UART_WriteTHR
 **			д���ͱ��ּĴ���
 ** \param [in] uart: UART0��UART1
 **				value: 8bit
 ** \return  none
 ** \note	
*****************************************************************************/
void UART_WriteTHR(UART0_Type* uart, uint32_t value);

/*****************************************************************************
 ** \brief	UART_ReadRBR
 **			�����ջ���Ĵ���
 ** \param [in] uart: UART0��UART1
 ** \return  8bit data
 ** \note	
*****************************************************************************/
uint32_t  UART_ReadRBR(UART0_Type* uart);

/*****************************************************************************
 ** \brief	UART_EnableCTSInt
 **			����CTS�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableCTSInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableCTSInt
 **			�ر�CTS�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableCTSInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableRTSInt
 **			����RTS�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableRTSInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableRTSInt
 **			�ر�RTS�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableRTSInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableXOFInt
 **			����XOFF�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableXOFInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableXOFInt
 **			�ر�XOF�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableXOFInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableModemInt
 **			����Modem�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableModemInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableModemInt
 **			�ر�Modem�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableModemInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableRxLineInt
 **			����������״̬�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableRxLineInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableRxLineInt
 **			�رս�����״̬�ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableRxLineInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableTHREInt
 **			�������ͱ��������ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableTHREInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableTHREInt
 **			�رշ��ͱ��������ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableTHREInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableRBRInt
 **			��������������Ч�жϺͽ��ն�ʱ������ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_EnableRBRInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableRBRInt
 **			�رս���������Ч�жϺͽ��ն�ʱ������ж�
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_DisableRBRInt(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableAuto
 **			����xx�߼�����
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_EnableAuto(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableAuto
 **			�ر�xx�߼�����
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_DisableAuto(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableFIFO
 **			����FIFO����
 ** \param [in] uart: UART0��UART1
 ** 			TxLevel: (1)FIFO_L0_1BYTE (2)FIFO_L1_4BYTE (3)FIFO_L2_8BYTE (4)FIFO_L3_14BYTE
 ** 			RxLevel: (1)FIFO_L0_1BYTE (2)FIFO_L1_4BYTE (3)FIFO_L2_8BYTE (4)FIFO_L3_14BYTE
 **				TxFIFOReset: (1)FIFO_RST_EN (2)FIFO_RST_DIS
 **				RxFIFOReset: (1)FIFO_RST_EN (2)FIFO_RST_DIS
 ** \return  none
 ** \note	FCR�Ĵ���Ϊֻд�Ĵ�������ȡFCR������Ϊ��Чֵ
*****************************************************************************/
void UART_EnableFIFO(UART0_Type* uart, uint32_t TxFIFOLvel, uint32_t RxFIFOLvel, uint32_t TxFIFOReset, uint32_t RxFIFOReset);
/*****************************************************************************
 ** \brief	UART_DisableFIFO
 **			�ر�FIFO����
 ** \param [in] uart: UART0��UART1
 ** \return  none
 ** \note	
*****************************************************************************/
void UART_DisableFIFO(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableRTS
**			����Ӳ������������
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_EnableRTS(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableRTS
 **			�ر�Ӳ������������
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_DisableRTS(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_EnableCTS
**			����Ӳ������������
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_EnableCTS(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_DisableCTS
 **			�ر�Ӳ������������
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void  UART_DisableCTS(UART0_Type* uart);

/*****************************************************************************
 ** \brief	UART_GetCTSState
 **			��ȡCTS����ܽ�״̬
 ** \param [in] uart: UART0��UART1
 ** \return 0���͵�ƽ   1���ߵ�ƽ
 ** \note	
*****************************************************************************/
uint32_t  UART_GetCTSState(UART0_Type* uart);

/*****************************************************************************
 ** \brief	UART_RTSSet
 **			RTS������ߵ�ƽ
 ** \param [in] uart: UART0��UART1
 ** \return 
 ** \note	
*****************************************************************************/
void UART_RTSSet(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_RTSClean
 **			RTS������͵�ƽ
 ** \param [in] uart: UART0��UART1
 ** \return 
 ** \note	
*****************************************************************************/
void UART_RTSClean(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_SetXON1AndXOFF1
 **			����XON1��XOFF1
 ** \param [in] uart: UART0��UART1
 **				Xon1 ��8λֵ
 **				Xoff1: 8λֵ
 ** \return 
 ** \note	
*****************************************************************************/
void UART_SetXON1AndXOFF1(UART0_Type* uart, uint8_t Xon1, uint8_t Xoff1);
/*****************************************************************************
 ** \brief	UART_SetXON2AndXOFF2
 **			RTS������͵�ƽ
 ** \param [in] uart: UART0��UART1
 **				Xon2 ��8λֵ
 **				Xoff2: 8λֵ
 ** \return 
 ** \note	
*****************************************************************************/
void UART_SetXON2AndXOFF2(UART0_Type* uart, uint8_t Xon2, uint8_t Xoff2);
/*****************************************************************************
 ** \brief	UART_EnableXONAndXOFF
 **			����XON_XOFFģʽ
 ** \param [in] uart: UART0��UART1
 **				Mode: (1)UART_USE_XON1_XOFF1
 **					  (2)UART_USE_XON2_XOFF2
 **					  (3)UART_USE_BOTH_XON_XOFF
 **						���������յ�����λ���ݣ���һ�� ������ XON1 ��ͬ��
 **                     �ڶ��������� XON2 ��ͬ���� XON ��Ч�� ͬ���������յ�����λ���ݣ�
 **                     ��һ������ �� XOFF1 ��ͬ���ڶ��������� XOFF2 ��ͬ���� XOFF ��Ч��
 ** \return none
 ** \note	
*****************************************************************************/
void UART_EnableXONAndXOFF(UART0_Type* uart, uint32_t Mode);
/*****************************************************************************
 ** \brief	UART_DisableXONAndXOFF
 **			�ر�XON_XOFFģʽ
 ** \param [in] uart: UART0��UART1
 ** \return none
 ** \note	
*****************************************************************************/
void UART_DisableXONAndXOFF(UART0_Type* uart);
/*****************************************************************************
 ** \brief	UART_GetXONAndXOFFState
 **			��ȡXON��XOFF״̬
 ** \param [in] uart: UART0��UART1
 ** \return 0�����յ�XON�ַ�  1�����յ�XOFF�ַ�
 ** \note	
*****************************************************************************/
uint32_t  UART_GetXONAndXOFFState(UART0_Type* uart);


#ifdef __cplusplus
}
#endif

#endif /* __UART_H_ */

