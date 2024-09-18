
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
//     uint8_t  SensorPlacement;       /*HALLλ�ã�DEGREES_120��DEGREES_60*/
//     int16_t  PhaseShift;            /*�� s16degree��λ�������λƫ��*/
//     uint16_t SpeedSamplingFreqHz;   /*�ٶȲ���Ƶ��*/
//     uint8_t  SpeedBufferSize;       /*�洢�ٶȼ���Ļ�������С*/
//     uint32_t TIMClockFreq;          /*!< Timer clock frequency express in Hz.*/

//     /*HALL state*/
//     uint8_t  HallState;              /*״̬*/
//     int8_t   Direction;              /*����*/
//     uint8_t  SensorIsReliable;  

//     /*Speed Angle*/
//     int32_t  SensorSpeed[HALL_SPEED_FIFO_SIZE];     /*�洢�������ڵĻ�����*/
//     uint8_t  SpeedFIFOIdx;                           /*����*/
//     volatile uint8_t BufferFilled;  /*��ʾ�ٶȻ������������Ĳ�������*/
//     int32_t  ElSpeedSum;           /*���ڼ���ƽ���ٶȼ���������ۼ�*/
//     uint32_t PseudoFreqConv;        /*ʱ������������ٶ�֮���ת�����ӣ���λFOCƵ��*/
//     int16_t  PrevRotorFreq;         /*�洢���һ����Ч�ĵ��ת��*/
//     int16_t  AvrElSpeedDpp;         /*ƽ���������ٶȣ���s16degree��ʾ*/

//     int16_t  MeasuredElAngle;       /*�ο��Ƕ�*/
//     int16_t  DeltaAngle;            /*�Ƕ�ƫ���λΪ s16degree*/
//     int16_t  CompSpeed;             /*ͬ����ǰ��ǶȺ�Ŀ���Ƕȵ��ٶȲ�������*/
    
//     uint16_t HALLMaxRatio;          /*��ʱ�����Ԥ��Ƶ�����ʣ�����������ٶȷ�����Ԥ��ֵ*/
//     uint16_t SatSpeed;              /*�����õ��ٶȳ���������ֵ���򷵻صı����ٶ�*/
//     uint32_t MaxPeriod;             /*�����ת�ٴ�����ͺ���ֵʱ�������������ź�֮������ʱ����*/
//     uint32_t MinPeriod;             /*�����ת�ٴ���������ֵʱ�������������ź�֮�����Сʱ������*/
//     uint16_t HallTimeout;           /*�����������ź�֮�������ӳ٣������ж����ٶȣ���λΪ����*/
//     uint16_t OvfFreq;               /*��ʱ�����Ƶ�ʣ�ͨ��ͨ����ʱ��ʱ��Ƶ�ʺ���������ֵ��65536������ó�*/

//     uint16_t PWMNbrPSamplingFreq;   /*��ʾ��ÿ���ٶȿ��������ڵ�FOC��������������*/
//     bool HallMtpa;                  /*���Ϊ�棬��ÿ�λ����������л�ʱֱ�����õ�ǰ�Ƕȣ�������ͨ��б�µ���*/

//     /*OV Flag or Status*/
//     volatile bool RatioDec;         /*��־���ڱ��ⶨʱ��Ԥ��Ƶ������������ݼ�*/
//     volatile bool RatioInc;
//     volatile uint8_t FirstCapt;
//     volatile uint8_t OVFCounter;
// }HALL_Handle_t;

// /**
//  * @brief  ����ٶȺ�λ�÷����ľ������
//  */
// typedef struct
// {
//     int16_t hElAngle;            /*ʵʱ��Ƕ�*/
//     int16_t hMecAngle;           /*��е�Ƕ�*/
//     int32_t wMecAngle;           // �߾��Ȼ�е�Ƕ�
//     int16_t hAvrMecSpeed01Hz;    // ƽ����е���ٶ�

//     int16_t hElSpeedDpp;         // ����ٶȣ������Ƕ�/���ڣ�dpp��
//     int16_t InstantaneousElSpeedDpp; // ˲ʱ����ٶ�

//     uint8_t bSpeedErrorNumber;   // �ٶȲ����������

//     uint8_t SpeedUnit;           // �ٶȵ�λֵ���� mc_stm_types.h �ж��壩
//     uint8_t bMaximumSpeedErrorsNumber;  // ����������Ч��������

//     uint8_t bElToMecRatio;       // ��������е����ת��ϵ����ͨ���ǵ����������
//     int16_t hMecAccel01HzP;      // ��е���ٶ�ֵ
//     uint16_t hMaxReliableMecSpeed01Hz;  // �����Ч��е�ٶ�
//     uint16_t hMinReliableMecSpeed01Hz;  // ��С��Ч��е�ٶ�
//     uint16_t hMaxReliableMecAccel01HzP; // �����Ч���ٶ�ֵ��Ĭ��ֵ 65535��

//     uint16_t hMeasurementFrequency; // ת�ӵ�ǶȲ���Ƶ�ʣ���λ Hz��
//     uint32_t DPPConvFactor;      // ����ٶ�ת�����ӣ�65536/PWM_FREQ_SCALING��
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
