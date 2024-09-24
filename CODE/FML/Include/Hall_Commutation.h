
#ifndef HALL_COMMUTATION_H 
#define HALL_COMMUTATION_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "FML_drivers.h"

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

#define DEAD_TIME                (200UL)       ///<����PWM������ʱ��
#define FOC_PERIOD               (100UL)        ///<FOC���Ĳ��ֵ�ִ������ (��λ:us)
#define SPEED_PERIOD             (1000UL)      ///<�ٶȸ������� (��λ:us)
/****************************SVPWM��ض���*********************************/
#define N0_PI                    (0.00000000000000f)  ///<0�㻡����
#define PI_3                     (1.04719755119660f)  ///<60�㻡����
#define N2_PI_3                  (2.09439510239320f)  ///<120�㻡����
#define N4_PI_3                  (4.18879020478640f)  ///<240�㻡����
#define N5_PI_3                  (5.23598775598299f)  ///<300�㻡����
#define N2_PI                    (6.28318530717959f)  ///<360�㻡����  

#define SQRT_3                   (1.73205080756888f) ///<����3
#define N1_SQRT_3                (0.57735026918963f) ///<1���Ը���3
#define N2_SQRT_3                (1.15470053837925f) ///<2���Ը���3
#define SQRT_3_2                 (0.86602540f)       ///<����3����2

                                                       
#define ROUND_TO_UINT8(x)        ((uint8_t)(x+0.5f))   ///<��������x(<127)��������Ϊuint8_t
#define ROUND_TO_UINT16(x)       ((uint16_t)(x+0.5f))  ///<��������x(<65535)��������Ϊuint16_t
#define ROUND_TO_UINT32(x)       ((uint32_t)(x+0.5f))  ///<��������x��������Ϊuint32_t       


#define ROUND_TO_INT8(x)         ((int8_t)(x+0.5f))    ///<��������x(<127)��������Ϊint8_t
#define ROUND_TO_INT16(x)        ((int16_t)(x+0.5f))   ///<��������x(<65535)��������Ϊint16_t
#define ROUND_TO_INT32(x)        ((int32_t)(x+0.5f))   ///<��������x��������Ϊint32_t
    /****************************������������ؽṹ��******************* **************/
    #define WBuffer_MAX_SIZE			(6UL)
	typedef struct {
		int8_t          last_direction;        //<��һ�εĵ��ת��
		int8_t          direction;             //<��ǰ�ĵ��ת��
    uint8_t         buffer_index;          //<��¼��ǰbuffer������±�
    uint8_t         last_state;            //<��һ�εĻ�����ֵ
    uint8_t         state;                 //<��ǰ�Ļ�����ֵ
    
    uint8_t         startup;                   //���������־λ
    uint8_t         directionChange;           //����ı��־
    uint8_t         locked;                    //������ת��־λ
    uint8_t         RatioDec;                  //Ԥ��Ƶ��С��־λ
    uint8_t         RatioInc;                  //Ԥ��Ƶ����־λ
	
    uint16_t        overcount;                 //<TIM��������ģʽ������ת�ٹ���CNT��������Ĵ���
	
    int32_t         buffer[WBuffer_MAX_SIZE];  //<WBuffer_MAX_SIZE=6
    int32_t         dpp_sum;                   //<���ڰ����滺��6����Ա�ۼӣ������ǻ�����ֵ�����ϵ�6���ִ������

    int32_t         prescaler;              //<��ǰTIM��ʵ��Ԥ��Ƶ
    int32_t         cap;					//<��ǰTIM��CCRx����ֵ
    int32_t         f_hall;            		//<�����жϵ�ִ��Ƶ��(ʵʱ��̬����)
    int32_t         f_speed;           		//<��Ƶ�ж�����ִ��Ƶ�ʣ�Ҳ���ٶ�ֵ���µ�Ƶ��
    int32_t         f_foc;             		//<��Ƶ�ж������Ƶ��
 		
 		/**�������ö�����65535��ʾ2PI����������صĲ����������ɽ��ʵ�ʴ������(dpp�Ƕ������Ƕȵ���˼)**/
 		/****************���ǵĵ�λ�������ٶ�ֵ/ÿfocִ������ ����Ҫ����ת��Ϊrad/s****************/
    int32_t         dpp_2;
    int32_t         dpp_1;
    int32_t         dpp;
    int32_t         avg_dpp;
    int32_t         comp_dpp;               //<���ڸ�����ȡ����
    int32_t         a_dpp;
		
		/**********************************����********************************************/

		/****************�����������Ͷ�����65535��ʾ2PI****************/
    int32_t         hall_theta;             //<ǿ��У׼ʱ����Ƕȵı�������ֵ����
    int32_t         offset_theta;           //<�������н��ܵĦý�
    int32_t         refer_theta;            //<��Ϊ��׼�ο���׷�ٵ�ָ��Ƕȱ�������ֵ����
    int32_t         delta_theta;            //<�������еĦ��ȣ���ֵ����
    int32_t         theta;                  //<ȥ׷�ٻ�׼ָ��ǶȵĽǶȱ���(��ֵ��)
		
		
		/*����ȫΪ������*/
		float           theta_inter;             //<��ֵ������ĽǶ�
		float		    omega_inter;             //<��ֵ��������ٶ�
		
}HALL_Struct;


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



/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
uint8_t Get_HallValue(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* HALL_COMMUTATION_H */
