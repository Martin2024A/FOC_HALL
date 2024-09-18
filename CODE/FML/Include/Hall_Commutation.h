
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
typedef struct
{
 SpeednPosFdbk_Handle_t _Super; 
  /* SW Settings */
  uint8_t  SensorPlacement; /*!< Define here the mechanical position of the sensors 
                             with reference to an electrical cycle.
                             Allowed values are: DEGREES_120 or DEGREES_60.*/
  
  int16_t  PhaseShift;  /*!< Define here in s16degree the electrical phase shift 
                             between the low to high transition of signal H1 and
                             the maximum of the Bemf induced on phase A.*/
  
  uint16_t SpeedSamplingFreqHz; /*!< Frequency (Hz) at which motor speed is to 
                             be computed. It must be equal to the frequency
                             at which function SPD_CalcAvrgMecSpeed01Hz
                             is called.*/
  
  uint8_t  SpeedBufferSize; /*!< Size of the buffer used to calculate the average 
                             speed. It must be less than 18.*/
  
								
  /* HW Settings */
  uint32_t TIMClockFreq; /*!< Timer clock frequency express in Hz.*/

  
  uint32_t H3Pin;      /*!< HALL sensor H3 channel GPIO output pin (if used,
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
  
  bool SensorIsReliable;            /*!< Flag to indicate a wrong configuration 
                                         of the Hall sensor signanls.*/
  
  volatile bool RatioDec;           /*!< Flag to avoid consecutive prescaler 
                                         decrement.*/
  volatile bool RatioInc;           /*!< Flag to avoid consecutive prescaler 
                                         increment.*/
  volatile uint8_t FirstCapt;      /*!< Flag used to discard first capture for
                                         the speed measurement*/
  volatile uint8_t BufferFilled;   /*!< Indicate the number of speed measuremt 
                                         present in the buffer from the start.
                                         It will be max bSpeedBufferSize and it
                                         is used to validate the start of speed
                                         averaging. If bBufferFilled is below
                                         bSpeedBufferSize the instantaneous
                                         measured speed is returned as average
                                         speed.*/
  volatile uint8_t OVFCounter;     /*!< Count overflows if prescaler is too low
                                         */
  int16_t SensorSpeed[HALL_SPEED_FIFO_SIZE];/*!< Holding the last 
                                         speed captures */
  uint8_t SpeedFIFOIdx;/*!< Pointer of next element to be stored in
                                         the speed sensor buffer*/
  int16_t  CurrentSpeed; /*!< Latest speed computed in HALL_IRQ_HANDLER*/
  
  int32_t  ElSpeedSum; /* Speed accumulator used to speed up the average speed computation*/
   
  int16_t PrevRotorFreq; /*!< Used to store the last valid rotor electrical 
                               speed in dpp used when HALL_MAX_PSEUDO_SPEED
                               is detected */
  int8_t Direction;          /*!< Instantaneous direction of rotor between two 
                               captures*/
  int8_t  NewSpeedAcquisition; /*!< Indacate that new speed information has 
                                     been stored in the buffer.*/
  
  int16_t AvrElSpeedDpp; /*!< It is the averaged rotor electrical speed express
                               in s16degree per current control period.*/
                          
  uint8_t HallState;     /*!< Current HALL state configuration */

  int16_t DeltaAngle;    /*!< Delta angle at the Hall sensor signal edge between
                               current electrical rotor angle of synchronism.
                               It is in s16degrees.*/
  int16_t MeasuredElAngle;/*!< This is the electrical angle  measured at each 
                               Hall sensor signal edge. It is considered the 
                               best measurement of electrical rotor angle.*/
  int16_t TargetElAngle; /*!< This is the electrical angle target computed at
                               speed control frequency based on hMeasuredElAngle.*/
  int16_t CompSpeed;     /*!< Speed compensation factor used to syncronize 
                               the current electrical angle with the target 
                               electrical angle. */
  
  uint16_t HALLMaxRatio; /*!< Max TIM prescaler ratio defining the lowest 
                             expected speed feedback.*/
  uint16_t SatSpeed;     /*!< Returned value if the measured speed is above the
                             maximum realistic.*/
  uint32_t PseudoFreqConv;/*!< Conversion factor between time interval Delta T
                             between HALL sensors captures, express in timer 
                             counts, and electrical rotor speed express in dpp.
                             Ex. Rotor speed (dpp) = wPseudoFreqConv / Delta T
                             It will be ((CKTIM / 6) / (SAMPLING_FREQ)) * 65536.*/
  
  uint32_t MaxPeriod;  /*!< Time delay between two sensor edges when the speed
                             of the rotor is the minimum realistic in the 
                             application: this allows to discriminate too low 
                             freq for instance.
                             This period shoud be expressed in timer counts and
                             it will be:
                             wMaxPeriod = ((10 * CKTIM) / 6) / MinElFreq(0.1Hz).*/
  
  uint32_t MinPeriod;
                        /*!< Time delay between two sensor edges when the speed
                             of the rotor is the maximum realistic in the 
                             application: this allows discriminating glitches 
                             for instance.
                             This period shoud be expressed in timer counts and
                             it will be:
                             wSpeedOverflow = ((10 * CKTIM) / 6) / MaxElFreq(0.1Hz).*/
  
  uint16_t HallTimeout;/*!< Max delay between two Hall sensor signal to assert
                             zero speed express in milliseconds.*/
  
  uint16_t OvfFreq;   /*!< Frequency of timer overflow (from 0 to 0x10000)
                             it will be: hOvfFreq = CKTIM /65536.*/
  uint16_t PWMNbrPSamplingFreq; /*!< Number of current control periods inside 
                             each speed control periods it will be: 
                             (hMeasurementFrequency / hSpeedSamplingFreqHz) - 1.*/
  
} HALL_Handle_t;

typedef struct {
  
  int16_t hElAngle;
  
  int16_t hMecAngle;
  
  int16_t hAvrMecSpeed01Hz;
  
  int16_t hElSpeedDpp;
  
  int16_t hMecAccel01HzP;
        
  uint8_t bSpeedErrorNumber;
  
  uint8_t bElToMecRatio;  /*!< Coefficient used to transform electrical to
                               mechanical quantities and viceversa. It usually
                               coincides with motor pole pairs number*/
  uint16_t hMaxReliableMecSpeed01Hz; /*!< Maximum value of measured speed that is
                                        considered to be valid. It's expressed
                                        in tenth of mechanical Hertz.*/
  uint16_t hMinReliableMecSpeed01Hz; /*!< Minimum value of measured speed that is
                                        considered to be valid. It's expressed
                                        in tenth of mechanical Hertz.*/
  uint8_t bMaximumSpeedErrorsNumber; /*!< Maximum value of not valid measurements
                                        before an error is reported.*/
  uint16_t hMaxReliableMecAccel01HzP; /*!< Maximum value of measured acceleration
                                        that is considered to be valid. It's
                                        expressed in 01HzP (tenth of Hertz per
                                        speed calculation period)*/
  uint16_t hMeasurementFrequency;  /*!< Frequency on which the user will request
                                    a measurement of the rotor electrical angle.
                                    It's also used to convert measured speed from
                                    tenth of Hz to dpp and viceversa.*/  
  
} SpeednPosFdbk_Handle_t;
void HALL_Init(HALL_Handle_t *pHandle);
void HALL_Clear(HALL_Handle_t *pHandle);


/*----------------------------------variable----------------------------------*/
extern uint8_t hall_index[6];
extern uint8_t sectorTableOfHall[7];
extern Motor_Sensor_t strSensor;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
uint8_t Get_HallValue(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* HALL_COMMUTATION_H */
