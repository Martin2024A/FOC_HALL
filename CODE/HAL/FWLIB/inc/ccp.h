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
/** \file ccp.h
**
** History:
** 
*****************************************************************************/
#ifndef __CCP_H_
#define __CCP_H_
 
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
 ** CCP 模块 & 通道
-----------------------------------------------------------------------------*/
#define		CCP0			(0x00UL)		/*CCP模块0*/
#define		CCP1			(0x01UL)		/*CCP模块1*/	
/*----------PWM模式/捕获模式0通道--------------------------------------------*/
#define		CCPxA			(0x00UL)
#define		CCPxB			(0x01UL)

/*----------捕获模式1内部通道------------------------------------------------*/
#define		CAP0			(0x00UL)
#define		CAP1			(0x01UL)
#define		CAP2			(0x02UL)
#define		CAP3			(0x03UL)
/*----------捕获模式1 内部通道都可选的外部通道-------------------------------*/
#define		ECAP00			(0x00UL)
#define		ECAP01			(0x01UL)
#define		ECAP02			(0x02UL)
#define		ECAP03			(0x03UL)

#define		ECAP10			(0x10UL)
#define		ECAP11			(0x11UL)
#define		ECAP12			(0x12UL)
#define		ECAP13			(0x13UL)

/*----------捕获模式1 可选ACMP通道---------------------------------------------*/
#define		CAP3_ACMP0		(0x38UL)
#define		CAP3_ACMP1		(0x39UL)
/*----------捕获模式1 可选CCPn通道---------------------------------------------*/
#define		CAP0_CCP0A		(0x0FUL)
#define		CAP1_CCP0B		(0x1FUL)
#define		CAP2_CCP1A		(0x2FUL)
#define		CAP3_CCP1B		(0x3FUL)


/*----------------------------------------------------------------------------
 ** CCP 模式
-----------------------------------------------------------------------------*/
#define		CCP_PWM_MODE		(0x00UL)		/*CCP模块PWM输出模式*/
#define 	CCP_CAP_MODE0		(0x01UL)		/*CCP模块捕获模式0*/
#define 	CCP_CAP_MODE1		(0x02UL)		/*CCP模块捕获模式1*/

/*----------------------------------------------------------------------------
 ** CCP 计数器重载模式
-----------------------------------------------------------------------------*/
#define		CCP_RELOAD_0XFFFF		(0x00)		/*计数器重加载值为0xFFFF*/
#define		CCP_RELOAD_CCPLOAD		(0x01)		/*计数器器重加载值为CCPxLOAD*/
/*----------------------------------------------------------------------------
 ** CCP 时钟
-----------------------------------------------------------------------------*/
#define		CCP_CLK_DIV_1		(0x00UL)		/*Fccp = PCLK/1*/
#define		CCP_CLK_DIV_4		(0x01UL)		/*Fccp = PCLK/4*/
#define		CCP_CLK_DIV_16		(0x02UL)		/*Fccp = PCLK/16*/
#define		CCP_CLK_DIV_64		(0x03UL)		/*Fccp = PCLK/64*/

/*----------------------------------------------------------------------------
 ** CCP 捕获模式
-----------------------------------------------------------------------------*/
/*----------捕获模式0---------------------------------------------*/
#define		CCP_CAP_MODE0_RISING				(0x00)	/*上升沿捕获*/
#define		CCP_CAP_MODE0_FALLING				(0x01)	/*下降沿捕获*/
#define		CCP_CAP_MODE0_RISING_TO_FALLING		(0x02)	/*捕获从上升沿到下降沿*/
#define		CCP_CAP_MODE0_FALLING_TO_RISING		(0x03)  /*捕获从下降沿到上升沿*/
/*----------捕获模式1------------------------------------------------*/
#define 	CCP_CAP_MODE1_DISABLE				(0x00)	/*捕获禁止*/
#define		CCP_CAP_MODE1_RISING				(0x01)	/*上升沿捕获*/
#define		CCP_CAP_MODE1_FALLING				(0x02)	/*下降沿捕获*/
#define		CCP_CAP_MODE1_BOTH_EDGE				(0x03)	/*双沿(下降沿&&上升沿)捕获*/
/*----------------------------------------------------------------------------
 ** CCP 写保护
-----------------------------------------------------------------------------*/
#define		CCP_P1A_WRITE_KEY		(0xAAUL)
#define		CCP_P1AB_WRITE_KEY		(0x55UL)





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
 ** \brief	CCP_Start
 **			开启CCP模块
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	 
*****************************************************************************/
void CCP_Start(uint32_t CCPn );
/*****************************************************************************
 ** \brief	CCP_Stop
 **			关闭CCP模块
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	 
*****************************************************************************/
void CCP_Stop(uint32_t CCPn );
/*****************************************************************************
 ** \brief	CCP_ConfigCLK
 **			设置CCPn模块时钟
 ** \param [in] CCPn : CCP0模块、CCP1模块
 **				ClkDiv:(1) CCP_CLK_DIV_1
 **					   (2) CCP_CLK_DIV_4
 **					   (3) CCP_CLK_DIV_16
 **					   (4) CCP_CLK_DIV_64
 **				ReloadMode: (1) CCP_RELOAD_0XFFFF    计数器重加载值为0xFFFF (连续模式)
 **							(2) CCP_RELOAD_CCPLOAD   计数器器重加载值为CCPxLOAD
 **				Preiod: 0x00~ 0xffff; （建议加载值不为0）		
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_ConfigCLK(uint32_t CCPn, uint32_t ClkDiv ,uint32_t ReloadMode, uint32_t Period);

/*****************************************************************************
 ** \brief	CCP_EnableRun
 **			CCPn开启
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnableRun(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_DisableRun
 **			CCPn关闭
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_DisableRun(uint32_t CCPn);

/*****************************************************************************
 ** \brief	CCP_EnablePWMMode
 **			开启PWM运行模式
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnablePWMMode(uint32_t CCPn);

/*****************************************************************************
 ** \brief	CCP_ConfigCompare
 **			设置CCPn模块通道n 比较值
 ** \param [in] CCPn : CCP0模块、CCP1模块
 **				CCPChannel: CCPxA 、CCPxB			
 **				Compare : 0x00~ 0xffff;
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_ConfigCompare(uint32_t CCPn, uint32_t CCPChannel ,uint32_t Compare);
/*****************************************************************************
 ** \brief	CCP_EnableReverseOutput
 **			开启反相输出
 ** \param [in] CCPn : CCP0模块、CCP1模块
 **				CCPChannel: CCPxA 、CCPxB
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnableReverseOutput(uint32_t CCPn, uint32_t CCPChannel);
/*****************************************************************************
 ** \brief	CCP_DisableReverseOutput
 **			关闭反相输出
 ** \param [in] CCPn : CCP0模块、CCP1模块
 **				CCPChannel: CCPxA 、CCPxB
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_DisableReverseOutput(uint32_t CCPn, uint32_t CCPChannel);
/*****************************************************************************
 ** \brief	CCP_EnableOverflowInt
 **			开启溢出中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnableOverflowInt(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_DisableOverflowInt
 **			关闭溢出中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_DisableOverflowInt(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_GetOverflowIntFlag
 **			获取溢出中断使能并溢出中断标志位
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  1:溢出中断使能并且产生中断  0:无中断
 ** \note	
*****************************************************************************/
uint32_t CCP_GetOverflowIntFlag(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_ClearOverflowIntFlag
 **			清除溢出中断标志位
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_ClearOverflowIntFlag(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_EnableCompareInt
 **			开启比较中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnableCompareInt(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_DisableCompareInt
 **			关闭比较中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_DisableCompareInt(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_GetCompareIntFlag
 **			获取比较中断使能并产生中断标志
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
uint32_t  CCP_GetCompareIntFlag(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_ClearCompareIntFlag
 **			清除比较中断标志
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_ClearCompareIntFlag(uint32_t CCPn);




/*****************************************************************************
 ** \brief	CCP_EnableCAPMode0
 **			开启捕获模式0
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_EnableCAPMode0(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_ConfigCAPMode0
 **			配置捕获模式0 的捕获方式
 ** \param [in] CCPn : CCP0模块、CCP1模块	
 **				Mode : (1)CCP_CAP_MODE0_RISING
 **					   (2)CCP_CAP_MODE0_FALLING
 **					   (3)CCP_CAP_MODE0_RISING_TO_FALLING
 **					   (4)CCP_CAP_MODE0_FALLING_TO_RISING
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_ConfigCAPMode0(uint32_t CCPn, uint32_t Mode);
/*****************************************************************************
 ** \brief	CCP_SelCAPMode0Channel
 **			选择捕获模式0 的捕获通道
 ** \param [in] CCPn : CCP0模块、CCP1模块	
 **				Channel : CCPxA 、CCPxB 
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_SelCAPMode0Channel(uint32_t CCPn, uint32_t Channel);
/*****************************************************************************
 ** \brief	CCP_GetCAPMode0Result
 **			获取捕获模式0 的捕获通道值
 ** \param [in] CCPn : CCP0模块、CCP1模块	
**				Channel : CCPxA 、CCPxB 
 ** \return  16bit result
 ** \note	
*****************************************************************************/
uint32_t  CCP_GetCAPMode0Result(uint32_t CCPn, uint32_t Channel);
/*****************************************************************************
 ** \brief	CCP_EnableCAPMode0Int
 **			开启捕获模式捕获中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_EnableCAPMode0Int(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_DisableCAPMode0Int
 **			关闭捕获模式捕获中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return  none
 ** \note	
*****************************************************************************/
void CCP_DisableCAPMode0Int(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_GetCAPMode0IntFlag
 **			获取捕获模式捕获中断使能并且产生中断
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return 1：产生中断  0:无中断
 ** \note	
*****************************************************************************/
uint32_t CCP_GetCAPMode0IntFlag(uint32_t CCPn);
/*****************************************************************************
 ** \brief	CCP_ClearCAPMode0IntFlag
 **			清除捕获模式捕获中断标志位
 ** \param [in] CCPn : CCP0模块、CCP1模块
 ** \return none
 ** \note	
*****************************************************************************/
void CCP_ClearCAPMode0IntFlag(uint32_t CCPn);





/*****************************************************************************
 ** \brief	CCP_EnableCAPMode1
 **			开启捕获模式1 
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_EnableCAPMode1(void);
/*****************************************************************************
 ** \brief	CCP_DisableCAPMode1
 **			关闭捕获模式1 
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_DisableCAPMode1(void);
/*****************************************************************************
 ** \brief	CCP_EnableCAPnReload
 **			开启捕获模式1下CAPn捕获触发CCP0加载
 ** \param [in] CAPn: CAP0、CAP1、CAP2、CAP3 
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_EnableCAPnReload(uint32_t CAPn);
/*****************************************************************************
 ** \brief	CCP_DisableCAPnReload
 **			关闭捕获模式1下CAPn捕获触发CCP0加载
 ** \param [in] CAPn: CAP0、CAP1、CAP2、CAP3 
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_DisableCAPnReload(uint32_t CAPn);

/*****************************************************************************
 ** \brief	CCP_ConfigCAPMode1
 **			配置捕获模式1 通道捕获模式
 ** \param [in] CAPn: CAP0、CAP1、CAP2、CAP3 
 **				Mode:(1)CCP_CAP_MODE1_RISING
 **					 (2)CCP_CAP_MODE1_FALLING
 **					 (3)CCP_CAP_MODE1_BOTH_EDGE
 **					 (4)CCP_CAP_MODE1_DISABLE
 ** \return  none
*****************************************************************************/
void  CCP_ConfigCAPMode1(uint32_t CAPn, uint32_t Mode);
/*****************************************************************************
 ** \brief	CCP_SelCAPMode1Channel
 **			选择捕获模式1 的捕获通道
 ** \param [in] CAPn: CAP0、CAP1、CAP2、CAP3 
 **				Channel :(1) ECAP00 ~ ECAP03
 **						 (2) ECAP10 ~ ECAP13
 **						 (3) CAP0_CCP0A 、CAP1_CCP0B、CAP2_CCP1A、CAP3_CCP1B
 **						 (4) CAP3_ACMP0、CAP3_ACMP1 ：  CAP3通道特有
 ** \return  none
 ** \note	
*****************************************************************************/
void  CCP_SelCAPMode1Channel(uint32_t CAPn, uint32_t Channel);
/*****************************************************************************
 ** \brief	CCP_TriggerCaputer
 **			写寄存器触发捕获功能
 ** \param [in] CAPn ：CAP0 、CAP1、CAP2 、CAP3
 								CHN: 0-CAP0, 1-CAP1, 2-CAP2, 3-CAP3
 ** \return  none
 ** \note	 
*****************************************************************************/
void CCP_TriggerCaputer(uint32_t CAPn,uint8_t CHN);
/*****************************************************************************
 ** \brief	CCP_GetCAPMode1Result
 **			获取捕获模式1 的捕获通道值
 ** \param [in] CAPn ：CAP0 、CAP1、CAP2 、CAP3	
 								CHN: 0-CAP0, 1-CAP1, 2-CAP2, 3-CAP3
 ** \return  16bit result
 ** \note	
*****************************************************************************/
uint32_t  CCP_GetCAPMode1Result(uint32_t CAPn,uint8_t CHN);
/*****************************************************************************
 ** \brief	CCP_EnableCAPMode1Int
 **			开启捕获模式1中断
 ** \param [in]CAPn ：CAP0 、CAP1、CAP2 、CAP3	
 ** \return  none
 ** \note	 
*****************************************************************************/
void CCP_EnableCAPMode1Int(uint32_t CAPn);
/*****************************************************************************
 ** \brief	CCP_DisableCAPMode1Int
 **			关闭捕获模式1中断
 ** \param [in]CAPn ：CAP0 、CAP1、CAP2 、CAP3	
 ** \return  none
 ** \note	 
*****************************************************************************/
void CCP_DisableCAPMode1Int(uint32_t CAPn);
/*****************************************************************************
 ** \brief	CCP_GetCAPMode1IntFlag
 **			获取捕获模式1中断使能并且产生中断标志位
 ** \param [in]CAPn ：CAP0 、CAP1、CAP2 、CAP3	
 ** \return  1:中断使能并且产生中断   0：无中断
 ** \note	 
*****************************************************************************/
uint32_t  CCP_GetCAPMode1IntFlag(uint32_t CAPn);
/*****************************************************************************
 ** \brief	CCP_ClearCAPMode1IntFlag
 **			清除捕获模式1中断标志位
 ** \param [in]CAPn ：CAP0 、CAP1、CAP2 、CAP3	
 ** \return  none
 ** \note	 
*****************************************************************************/
void  CCP_ClearCAPMode1IntFlag(uint32_t CAPn);

#ifdef __cplusplus
}
#endif

#endif /* __CCP_H_ */

