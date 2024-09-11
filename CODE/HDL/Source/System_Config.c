
/*----------------------------------include-----------------------------------*/
#include "System_Config.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void System_Init(void)
{
	SYS_DisableIOCFGProtect();			/*�ر�IOCONFIGд����*/
	SYS_DisableGPIO0Protect();			/*�ر�GPIO0����ؼĴ���д����*/
	SYS_DisableGPIO1Protect();			/*�ر�GPIO1����ؼĴ���д����*/
	SYS_DisableGPIO2Protect();			/*�ر�GPIO2����ؼĴ���д����*/
	SYS_DisableGPIO3Protect();			/*�ر�GPIO3����ؼĴ���д����*/
	SYS_DisableGPIO4Protect();			/*�ر�GPIO4����ؼĴ���д����*/	
	
	SYS_ConfigHSI(SYS_CLK_HSI_48M);		/*�����ڲ�����ʱ��Ϊ48Mhz*/
	SYS_EnableHSI();					/*��������ʱ��*/
	SYS_ConfigAHBClock(SYS_CLK_SEL_HSI,SYS_CLK_DIV_1);	/*����AHBʱ��Ϊ����ʱ�ӵ�1��Ƶ*/
	SYS_ConfigAPBClock(AHB_CLK_DIV_1);					/*����APBʱ��ΪAHBʱ�ӵ�1��Ƶ*/
	SystemCoreClockUpdate();							/*ˢ��SystemCoreCLk��SystemAPBClock����ֵ*/
}
/*------------------------------------test------------------------------------*/
