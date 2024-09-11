
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


/*----------------------------------variable----------------------------------*/
extern uint8_t hall_index[6];
extern uint8_t sectorTableOfHall[7];
extern Motor_Sensor_t strSensor;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
uint8_t get_hallValue(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* HALL_COMMUTATION_H */
