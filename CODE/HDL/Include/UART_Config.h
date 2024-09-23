
#ifndef UART_DEBUG_H 
#define UART_DEBUG_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include <stdint.h>
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
extern uint8_t U_ReceiveData[16];
extern volatile uint32_t U_RxdFlag;

extern uint8_t U_SendData[16];
extern volatile uint32_t U_TxdFlag;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void UART_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendString(char *String);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendPacket(void);
uint8_t Uart1_getchar(void);
uint8_t Serial_GetRxFlag(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* UART_DEBUG_H */
