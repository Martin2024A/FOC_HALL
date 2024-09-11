
#ifndef HALL_COMMUTATION_H 
#define HALL_COMMUTATION_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "CMS32M55xx.h"
#include "UART_Config.h"
#include "stdbool.h"
/*-----------------------------------macro------------------------------------*/
#define SENSOR_MODE 1

#define HALL_A          0x04
#define HALL_B          0x02
#define HALL_C          0x01

#define HALL_A_IO		((GPIO3->GPIO0DI)&0x02)
#define HALL_B_IO		((GPIO3->GPIO0DI)&0x04)
#define HALL_C_IO		((GPIO3->GPIO0DI)&0x10)
/*----------------------------------typedef-----------------------------------*/
typedef struct 
{
	uint8_t ModeEn;

	uint8_t Hall_A;
	uint8_t Hall_B;
	uint8_t Hall_C;

	uint8_t hallNow;
	uint8_t hallLast;
	uint8_t HallSector;

}Motor_Sensor_t;

//     /****************************霍尔传感器相关结构体******************* **************/
//     #define WBuffer_MAX_SIZE			(6UL)
// 	typedef struct {
// 		int8_t          last_direction;        //<上一次的电机转向
// 		int8_t          direction;             //<当前的电机转向
//     	uint8_t         buffer_index;          //<记录当前buffer缓存的下标
//     	uint8_t         last_state;            //<上一次的霍尔真值
//     	uint8_t         state;                 //<当前的霍尔真值
    
// 	  	uint8_t         startup;                   //电机启动标志位
// 	  	uint8_t         directionChange;           //方向改变标志
// 	  	uint8_t         locked;                    //霍尔堵转标志位
//       	uint8_t         RatioDec;                  //预分频变小标志位
//       	uint8_t         RatioInc;                  //预分频变大标志位
	
// 	  	uint16_t        overcount;                 //<TIM霍尔捕获模式下因电机转速过慢CNT计数溢出的次数
	
//       	int32_t         buffer[WBuffer_MAX_SIZE];  //<WBuffer_MAX_SIZE=6
//       	int32_t         dpp_sum;                   //<用于把上面缓存6个成员累加，过程是滑动均值，请结合第6部分代码分析
		
//       	int32_t         prescaler;              //<当前TIM的实际预分频
//       	int32_t         cap;					//<当前TIM的CCRx捕获值
//       	int32_t         f_hall;            		//<霍尔中断的执行频率(实时动态计算)
//       	int32_t         f_speed;           		//<中频中断任务执行频率，也是速度值更新的频率
//       	int32_t         f_foc;             		//<高频中断任务的频率
 		
//  		/**程序中用定点数65535表示2PI，这里是相关的操作变量，可结合实际代码理解(dpp是定点数角度的意思)**/
//  		/****************它们的单位：整型速度值/每foc执行周期 ，需要后期转化为rad/s****************/
//       	int32_t         dpp_2;
//       	int32_t         dpp_1;
//       	int32_t         dpp;
//       	int32_t         avg_dpp;
//       	int32_t         comp_dpp;               //<用于辅助求取Δθ
//       	int32_t         a_dpp;
		
// 		/**********************************结束********************************************/

// 		/****************它们仍是整型定点数65535表示2PI****************/
// 	  	int32_t         hall_theta;             //<强制校准时保存角度的变量（插值法）
//       	int32_t         offset_theta;           //<就是文中介绍的γ角
//       	int32_t         refer_theta;            //<作为基准参考被追踪的指标角度变量（插值法）
//       	int32_t         delta_theta;            //<就是文中的Δθ（插值法）
//       	int32_t         theta;                  //<去追踪基准指标角度的角度变量(插值法)
		
		
// 		/*以下全为浮点型*/
// 		float           theta_inter;             //<插值法估算的角度
// 		float		    omega_inter;             //<插值法估算的速度
		
// 		float			pll_kp;
// 		float			pll_ki;
// 		float           pll_theta;               //<锁相环法估算的角度
// 		float			pll_omega;               //<锁相环法估算的速度
// 		float			pll_Te;                  //<锁相环执行周期
// }HALL_Struct;

/*----------------------------------variable----------------------------------*/
extern uint8_t hall_index[6];
extern uint8_t sectorTableOfHall[7];
extern Motor_Sensor_t strSensor;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void MC_SensorMode_HallChange(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* HALL_COMMUTATION_H */
