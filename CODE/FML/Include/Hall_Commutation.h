
#ifndef HALL_COMMUTATION_H 
#define HALL_COMMUTATION_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/


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

#define DEAD_TIME                (200UL)       ///<互补PWM的死区时间
#define FOC_PERIOD               (100UL)        ///<FOC核心部分的执行周期 (单位:us)
#define SPEED_PERIOD             (1000UL)      ///<速度更新周期 (单位:us)
/****************************SVPWM相关定义*********************************/
#define N0_PI                    (0.00000000000000f)  ///<0°弧度制
#define PI_3                     (1.04719755119660f)  ///<60°弧度制
#define N2_PI_3                  (2.09439510239320f)  ///<120°弧度制
#define N4_PI_3                  (4.18879020478640f)  ///<240°弧度制
#define N5_PI_3                  (5.23598775598299f)  ///<300°弧度制
#define N2_PI                    (6.28318530717959f)  ///<360°弧度制  

#define SQRT_3                   (1.73205080756888f) ///<根号3
#define N1_SQRT_3                (0.57735026918963f) ///<1除以根号3
#define N2_SQRT_3                (1.15470053837925f) ///<2除以根号3
#define SQRT_3_2                 (0.86602540f)       ///<根号3除以2

                                                       
#define ROUND_TO_UINT8(x)        ((uint8_t)(x+0.5f))   ///<将浮点数x(<127)四舍五入为uint8_t
#define ROUND_TO_UINT16(x)       ((uint16_t)(x+0.5f))  ///<将浮点数x(<65535)四舍五入为uint16_t
#define ROUND_TO_UINT32(x)       ((uint32_t)(x+0.5f))  ///<将浮点数x四舍五入为uint32_t       


#define ROUND_TO_INT8(x)         ((int8_t)(x+0.5f))    ///<将浮点数x(<127)四舍五入为int8_t
#define ROUND_TO_INT16(x)        ((int16_t)(x+0.5f))   ///<将浮点数x(<65535)四舍五入为int16_t
#define ROUND_TO_INT32(x)        ((int32_t)(x+0.5f))   ///<将浮点数x四舍五入为int32_t
    /****************************霍尔传感器相关结构体******************* **************/
    #define WBuffer_MAX_SIZE			(6UL)
	typedef struct {
		int8_t          last_direction;        //<上一次的电机转向
		int8_t          direction;             //<当前的电机转向
    uint8_t         buffer_index;          //<记录当前buffer缓存的下标
    uint8_t         last_state;            //<上一次的霍尔真值
    uint8_t         state;                 //<当前的霍尔真值
    
    uint8_t         startup;                   //电机启动标志位
    uint8_t         directionChange;           //方向改变标志
    uint8_t         locked;                    //霍尔堵转标志位
    uint8_t         RatioDec;                  //预分频变小标志位
    uint8_t         RatioInc;                  //预分频变大标志位
	
    uint16_t        overcount;                 //<TIM霍尔捕获模式下因电机转速过慢CNT计数溢出的次数
	
    int32_t         buffer[WBuffer_MAX_SIZE];  //<WBuffer_MAX_SIZE=6
    int32_t         dpp_sum;                   //<用于把上面缓存6个成员累加，过程是滑动均值，请结合第6部分代码分析

    int32_t         prescaler;              //<当前TIM的实际预分频
    int32_t         cap;					//<当前TIM的CCRx捕获值
    int32_t         f_hall;            		//<霍尔中断的执行频率(实时动态计算)
    int32_t         f_speed;           		//<中频中断任务执行频率，也是速度值更新的频率
    int32_t         f_foc;             		//<高频中断任务的频率
 		
 		/**程序中用定点数65535表示2PI，这里是相关的操作变量，可结合实际代码理解(dpp是定点数角度的意思)**/
 		/****************它们的单位：整型速度值/每foc执行周期 ，需要后期转化为rad/s****************/
    int32_t         dpp_2;
    int32_t         dpp_1;
    int32_t         dpp;
    int32_t         avg_dpp;
    int32_t         comp_dpp;               //<用于辅助求取Δθ
    int32_t         a_dpp;
		
		/**********************************结束********************************************/

		/****************它们仍是整型定点数65535表示2PI****************/
    int32_t         hall_theta;             //<强制校准时保存角度的变量（插值法）
    int32_t         offset_theta;           //<就是文中介绍的γ角
    int32_t         refer_theta;            //<作为基准参考被追踪的指标角度变量（插值法）
    int32_t         delta_theta;            //<就是文中的Δθ（插值法）
    int32_t         theta;                  //<去追踪基准指标角度的角度变量(插值法)
		
		
		/*以下全为浮点型*/
		float           theta_inter;             //<插值法估算的角度
		float		    omega_inter;             //<插值法估算的速度
		
}HALL_Struct;


#define HALL_SPEED_FIFO_SIZE  ((uint8_t)18)
#define DEGREES_120 0u
#define DEGREES_60 1u

// typedef struct 
// {
//     SpeednPosFdbk_Handle_t _Super;
//     /*SW Settings*/
//     uint8_t  SensorPlacement;       /*HALL位置：DEGREES_120、DEGREES_60*/
//     int16_t  PhaseShift;            /*用 s16degree单位定义的相位偏移*/
//     uint16_t SpeedSamplingFreqHz;   /*速度采样频率*/
//     uint8_t  SpeedBufferSize;       /*存储速度计算的缓冲区大小*/
//     uint32_t TIMClockFreq;          /*!< Timer clock frequency express in Hz.*/

//     /*HALL state*/
//     uint8_t  HallState;              /*状态*/
//     int8_t   Direction;              /*方向*/
//     uint8_t  SensorIsReliable;  

//     /*Speed Angle*/
//     int32_t  SensorSpeed[HALL_SPEED_FIFO_SIZE];     /*存储捕获周期的缓冲区*/
//     uint8_t  SpeedFIFOIdx;                           /*索引*/
//     volatile uint8_t BufferFilled;  /*表示速度缓冲区中已填充的测量次数*/
//     int32_t  ElSpeedSum;           /*用于加速平均速度计算的周期累加*/
//     uint32_t PseudoFreqConv;        /*时间间隔与电机电角速度之间的转换因子，单位FOC频率*/
//     int16_t  PrevRotorFreq;         /*存储最后一次有效的电机转速*/
//     int16_t  AvrElSpeedDpp;         /*平均电机电角速度，以s16degree表示*/

//     int16_t  MeasuredElAngle;       /*参考角度*/
//     int16_t  DeltaAngle;            /*角度偏差，单位为 s16degree*/
//     int16_t  CompSpeed;             /*同步当前电角度和目标电角度的速度补偿因子*/
    
//     uint16_t HALLMaxRatio;          /*定时器最大预分频器比率，定义了最低速度反馈的预期值*/
//     uint16_t SatSpeed;              /*如果测得的速度超过最大合理值，则返回的饱和速度*/
//     uint32_t MaxPeriod;             /*当电机转速处于最低合理值时，霍尔传感器信号之间的最大时间间隔*/
//     uint32_t MinPeriod;             /*当电机转速处于最大合理值时，霍尔传感器信号之间的最小时间间隔。*/
//     uint16_t HallTimeout;           /*霍尔传感器信号之间的最大延迟，用于判断零速度，单位为毫秒*/
//     uint16_t OvfFreq;               /*定时器溢出频率，通常通过定时器时钟频率和最大计数器值（65536）计算得出*/

//     uint16_t PWMNbrPSamplingFreq;   /*表示在每次速度控制周期内的FOC电流控制周期数*/
//     bool HallMtpa;                  /*如果为真，则每次霍尔传感器切换时直接设置当前角度，而无需通过斜坡调整*/

//     /*OV Flag or Status*/
//     volatile bool RatioDec;         /*标志用于避免定时器预分频器连续递增或递减*/
//     volatile bool RatioInc;
//     volatile uint8_t FirstCapt;
//     volatile uint8_t OVFCounter;
// }HALL_Handle_t;

// /**
//  * @brief  电机速度和位置反馈的句柄定义
//  */
// typedef struct
// {
//     int16_t hElAngle;            /*实时电角度*/
//     int16_t hMecAngle;           /*机械角度*/
//     int32_t wMecAngle;           // 高精度机械角度
//     int16_t hAvrMecSpeed01Hz;    // 平均机械角速度

//     int16_t hElSpeedDpp;         // 电角速度（增量角度/周期，dpp）
//     int16_t InstantaneousElSpeedDpp; // 瞬时电角速度

//     uint8_t bSpeedErrorNumber;   // 速度测量错误次数

//     uint8_t SpeedUnit;           // 速度单位值（在 mc_stm_types.h 中定义）
//     uint8_t bMaximumSpeedErrorsNumber;  // 允许的最大无效测量次数

//     uint8_t bElToMecRatio;       // 电气到机械量的转换系数（通常是电机极对数）
//     int16_t hMecAccel01HzP;      // 机械加速度值
//     uint16_t hMaxReliableMecSpeed01Hz;  // 最大有效机械速度
//     uint16_t hMinReliableMecSpeed01Hz;  // 最小有效机械速度
//     uint16_t hMaxReliableMecAccel01HzP; // 最大有效加速度值（默认值 65535）

//     uint16_t hMeasurementFrequency; // 转子电角度测量频率（单位 Hz）
//     uint32_t DPPConvFactor;      // 电角速度转换因子（65536/PWM_FREQ_SCALING）
// } SpeednPosFdbk_Handle_t;



/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
uint8_t Get_HallValue(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* HALL_COMMUTATION_H */
