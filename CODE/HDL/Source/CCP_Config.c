
/*----------------------------------include-----------------------------------*/
#include "CCP_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void CCP_Init(void)
{
	/*
	(1)����CCP��ʱ��
	*/
	SYS_EnablePeripheralClk(SYS_CLK_CCP_MSK);						/*����CCPģ��ʱ��*/
	CCP_ConfigCLK(CCP1,CCP_CLK_DIV_64,CCP_RELOAD_CCPLOAD,4800);		/*Fccp = 48Mhz /64 = 0.75Mh ->����������� = 4800/0.75Mhz = 6400us*/
	
	/*
	(2)����CCP����ģʽ
	*/
	CCP_EnableCAPMode1();								/*����CCPģ�鹤��ģʽΪ����ģʽ1*/
	CCP_ConfigCAPMode1(CAP0,CCP_CAP_MODE1_BOTH_EDGE);		/*���ò���ͨ��ΪCAP0�������ز���*/

	/*
	(3)����CCP����ͨ��
	*/
	CCP_SelCAPMode1Channel(CAP0,ECAP10);				/*CAP0ͨ��ѡ�������ⲿECAP02�ӿ�*/
	SYS_SET_IOCFG(IOP31CFG,SYS_IOCFG_P31_ECAP10);		/*����P15ΪECAP02*/
	CCP_SelCAPMode1Channel(CAP0,ECAP11);
	SYS_SET_IOCFG(IOP32CFG,SYS_IOCFG_P32_ECAP11);
	CCP_SelCAPMode1Channel(CAP0,ECAP12);
	SYS_SET_IOCFG(IOP34CFG,SYS_IOCFG_P34_GECAP12);     //�궨������д���ˣ�
	/*
	(4)����CCP�����ж�
	*/		
	CCP_EnableOverflowInt(CCP1);					   /*����CCP1����ж�*/
	CCP_EnableCAPMode1Int(CAP0);					   /*����CAP0ͨ�������ж�*/
	NVIC_EnableIRQ(CCP_IRQn);	
	/*
	(5)����CCP �ж����ȼ�
	*/	
	NVIC_SetPriority(CCP_IRQn,3);					/*���ȼ�0~3�� 0��ߡ�3���*/		
	/*
	(6)����CCPģ��
	*/	
	CCP_EnableRun(CCP1);			
	CCP_Start(CCP1);				
}


/*------------------------------------test------------------------------------*/
