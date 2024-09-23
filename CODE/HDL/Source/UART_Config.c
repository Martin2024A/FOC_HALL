
/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
uint8_t U_ReceiveData[16] ={0};
volatile uint32_t U_RxdFlag =0;

uint8_t U_SendData[16]={0};
volatile uint32_t U_TxdFlag =0;


static volatile uint32_t U_IntID;
static volatile uint32_t U_LSRFlag;
static volatile uint32_t U_count;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void UART_Init(void)
{	
	/*
	1.设置UART 时钟
	*/	
	SYS_EnablePeripheralClk(SYS_CLK_UART1_MSK);

	/*
	2.设置UART 模式
	*/
	UART_ConfigRunMode(UART1, 9600, UART_WLS_8, UART_PARITY_NONE,UART_STOP_BIT_1);
	UART_EnableAuto(UART1);
	UART_EnableFIFO(UART1,FIFO_L0_1BYTE, FIFO_L0_1BYTE, FIFO_RST_EN, FIFO_RST_EN);	

	/*
	3.设置UART 接口
	*/	
	SYS_SET_IOCFG(IOP43CFG,SYS_IOCFG_P43_RXD1);	
	SYS_SET_IOCFG(IOP17CFG,SYS_IOCFG_P17_TXD1);	

	/*
	4.设置UART 中断
	*/	
	UART_EnableTHREInt(UART1);
	UART_EnableRBRInt(UART1);
}

void Serial_SendByte(uint8_t Byte)
{
	while(!(UART1->LSR & UART_LSR_THRE_Msk));//等待发送完成
	UART1->THR = Byte;
}
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	{
		Serial_SendByte(String[i]);		//依次调用Serial_SendByte发送每个字节数据
	}
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)		//遍历数组
	{
		Serial_SendByte(Array[i]);		//依次调用Serial_SendByte发送每个字节数据
	}
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(U_SendData, 4);
	Serial_SendByte(0xFE);
}


uint8_t Uart1_getchar(void)
{
	while(!(UART1->LSR & UART_LSR_RDR_Msk));
	return  UART1->RBR;
}

uint8_t Serial_GetRxFlag(void)
{
	if (U_RxdFlag == 1)			//如果标志位为1
	{
		U_RxdFlag = 0;
		return 1;					//则返回1，并自动清零标志位
	}
	return 0;						//如果标志位为0，则返回0
}

void UART1_IRQHandler(void)
{
/*----------------------------------------------------------------------------------------*/	
	U_IntID = (UART1->IIR & 0x0F);			//获取中断事件ID。此处不能打断点，会导致状态位丢失，读取后IIR寄存器值将会改变 
	U_IntID = U_IntID >>1;
	U_LSRFlag = UART1->LSR;
	
	switch(U_IntID)							//处理事件
	{
		case 0:								//Modem 状态改变
			break;
		case 0x1:							//THR 寄存器为空 （发送后 THR的值会自动清除）		
			U_TxdFlag =1;		
		  break;
					
		case 0x2:							// FIFO接收到数据后，并等于设置的FIFO等级，则产生中断		
		
			break;		
		case 0x3:							//Rx line 状态变化 ->监测LSR[4:1]	

			if(U_LSRFlag & (1<<1))			//FIFO溢出
			{
					
			}	
			if(U_LSRFlag & (1<<2))			//PE
			{
				
			}	
			if(U_LSRFlag & (1<<3))			//FE
			{
				
			}	
			if(U_LSRFlag & (1<<4))			//BI
			{
				
			}	
			// UART_EnableFIFO(UART0,FIFO_L0_1BYTE, FIFO_L0_1BYTE, FIFO_RST_DIS, FIFO_RST_EN);					
			break;		
		case 0x6:					//1帧数据的定时时间内未接收到新数据,触发FIFO 接收定时溢出中断		
			U_count =0;
			while(UART1->LSR & UART_LSR_RDR_Msk)
			{
				U_ReceiveData[U_count++] = UART_ReadRBR(UART1);
			}	
			U_RxdFlag = 1;
		//			UART_EnableFIFO(UART0,FIFO_L0_1BYTE, FIFO_L1_4BYTE, FIFO_RST_DIS, FIFO_RST_EN);	/*清除掉接收FIFO*/ 			
			break;		
	}
}
/*------------------------------------test------------------------------------*/
