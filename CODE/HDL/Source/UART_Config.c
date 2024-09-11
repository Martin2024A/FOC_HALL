
/*----------------------------------include-----------------------------------*/
#include "UART_Config.h"
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
	SYS_EnablePeripheralClk(SYS_CLK_UART1_MSK);
	UART_ConfigRunMode(UART1, 9600, UART_WLS_8, UART_PARITY_NONE,UART_STOP_BIT_1);
	
	UART_EnableAuto(UART1);
	UART_EnableFIFO(UART1,FIFO_L0_1BYTE, FIFO_L0_1BYTE, FIFO_RST_EN, FIFO_RST_EN);	
	
	SYS_SET_IOCFG(IOP43CFG,SYS_IOCFG_P43_RXD1);	
	SYS_SET_IOCFG(IOP17CFG,SYS_IOCFG_P17_TXD1);	

	UART_EnableTHREInt(UART1);
	UART_EnableRBRInt(UART1);
}

void Serial_SendByte(uint8_t Byte)
{
	while(!(UART1->LSR & UART_LSR_THRE_Msk));//�ȴ��������
	UART1->THR = Byte;
}

uint8_t Uart1_getchar(void)
{
	while(!(UART1->LSR & UART_LSR_RDR_Msk));
	return  UART1->RBR;
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)//�����ַ����飨�ַ������������ַ���������־λ��ֹͣ
	{
		Serial_SendByte(String[i]);		//���ε���Serial_SendByte����ÿ���ֽ�����
	}
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)		//��������
	{
		Serial_SendByte(Array[i]);		//���ε���Serial_SendByte����ÿ���ֽ�����
	}
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(U_SendData, 4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if (U_RxdFlag == 1)			//�����־λΪ1
	{
		U_RxdFlag = 0;
		return 1;					//�򷵻�1�����Զ������־λ
	}
	return 0;						//�����־λΪ0���򷵻�0
}

void UART1_IRQHandler(void)
{
/*----------------------------------------------------------------------------------------*/	
	U_IntID = (UART1->IIR & 0x0F);		//��ȡ�ж��¼�ID���˴����ܴ�ϵ㣬�ᵼ��״̬λ��ʧ����ȡ��IIR�Ĵ���ֵ����ı� 
	U_IntID = U_IntID >>1;
	U_LSRFlag = UART1->LSR;
	
	switch(U_IntID)								//�����¼�
	{
		case 0:										//Modem ״̬�ı�
			break;
		case 0x1:									//THR �Ĵ���Ϊ�� �����ͺ� THR��ֵ���Զ������		
			U_TxdFlag =1;		
		  break;
					
		case 0x2:									// FIFO���յ����ݺ󣬲��������õ�FIFO�ȼ���������ж�		
		
			break;		
		case 0x3:									//Rx line ״̬�仯 ->���LSR[4:1]	

			if(U_LSRFlag & (1<<1))				//FIFO���
			{
					
			}	
			if(U_LSRFlag & (1<<2))				//PE
			{
				
			}	
			if(U_LSRFlag & (1<<3))				//FE
			{
				
			}	
			if(U_LSRFlag & (1<<4))				//BI
			{
				
			}	
//			UART_EnableFIFO(UART0,FIFO_L0_1BYTE, FIFO_L0_1BYTE, FIFO_RST_DIS, FIFO_RST_EN);					
			break;		
		case 0x6:					//1֡���ݵĶ�ʱʱ����δ���յ�������,����FIFO ���ն�ʱ����ж�		
			U_count =0;
			while(UART1->LSR & UART_LSR_RDR_Msk)
			{
				U_ReceiveData[U_count++] = UART_ReadRBR(UART1);
			}	
			U_RxdFlag = 1;
		//			UART_EnableFIFO(UART0,FIFO_L0_1BYTE, FIFO_L1_4BYTE, FIFO_RST_DIS, FIFO_RST_EN);	/*���������FIFO*/ 			
			break;		
	}
	
}
/*------------------------------------test------------------------------------*/
