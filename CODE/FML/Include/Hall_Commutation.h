
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

//     /****************************������������ؽṹ��******************* **************/
//     #define WBuffer_MAX_SIZE			(6UL)
// 	typedef struct {
// 		int8_t          last_direction;        //<��һ�εĵ��ת��
// 		int8_t          direction;             //<��ǰ�ĵ��ת��
//     	uint8_t         buffer_index;          //<��¼��ǰbuffer������±�
//     	uint8_t         last_state;            //<��һ�εĻ�����ֵ
//     	uint8_t         state;                 //<��ǰ�Ļ�����ֵ
    
// 	  	uint8_t         startup;                   //���������־λ
// 	  	uint8_t         directionChange;           //����ı��־
// 	  	uint8_t         locked;                    //������ת��־λ
//       	uint8_t         RatioDec;                  //Ԥ��Ƶ��С��־λ
//       	uint8_t         RatioInc;                  //Ԥ��Ƶ����־λ
	
// 	  	uint16_t        overcount;                 //<TIM��������ģʽ������ת�ٹ���CNT��������Ĵ���
	
//       	int32_t         buffer[WBuffer_MAX_SIZE];  //<WBuffer_MAX_SIZE=6
//       	int32_t         dpp_sum;                   //<���ڰ����滺��6����Ա�ۼӣ������ǻ�����ֵ�����ϵ�6���ִ������
		
//       	int32_t         prescaler;              //<��ǰTIM��ʵ��Ԥ��Ƶ
//       	int32_t         cap;					//<��ǰTIM��CCRx����ֵ
//       	int32_t         f_hall;            		//<�����жϵ�ִ��Ƶ��(ʵʱ��̬����)
//       	int32_t         f_speed;           		//<��Ƶ�ж�����ִ��Ƶ�ʣ�Ҳ���ٶ�ֵ���µ�Ƶ��
//       	int32_t         f_foc;             		//<��Ƶ�ж������Ƶ��
 		
//  		/**�������ö�����65535��ʾ2PI����������صĲ����������ɽ��ʵ�ʴ������(dpp�Ƕ������Ƕȵ���˼)**/
//  		/****************���ǵĵ�λ�������ٶ�ֵ/ÿfocִ������ ����Ҫ����ת��Ϊrad/s****************/
//       	int32_t         dpp_2;
//       	int32_t         dpp_1;
//       	int32_t         dpp;
//       	int32_t         avg_dpp;
//       	int32_t         comp_dpp;               //<���ڸ�����ȡ����
//       	int32_t         a_dpp;
		
// 		/**********************************����********************************************/

// 		/****************�����������Ͷ�����65535��ʾ2PI****************/
// 	  	int32_t         hall_theta;             //<ǿ��У׼ʱ����Ƕȵı�������ֵ����
//       	int32_t         offset_theta;           //<�������н��ܵĦý�
//       	int32_t         refer_theta;            //<��Ϊ��׼�ο���׷�ٵ�ָ��Ƕȱ�������ֵ����
//       	int32_t         delta_theta;            //<�������еĦ��ȣ���ֵ����
//       	int32_t         theta;                  //<ȥ׷�ٻ�׼ָ��ǶȵĽǶȱ���(��ֵ��)
		
		
// 		/*����ȫΪ������*/
// 		float           theta_inter;             //<��ֵ������ĽǶ�
// 		float		    omega_inter;             //<��ֵ��������ٶ�
		
// 		float			pll_kp;
// 		float			pll_ki;
// 		float           pll_theta;               //<���໷������ĽǶ�
// 		float			pll_omega;               //<���໷��������ٶ�
// 		float			pll_Te;                  //<���໷ִ������
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
