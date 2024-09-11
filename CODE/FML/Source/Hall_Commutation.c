
/*----------------------------------include-----------------------------------*/
#include "Hall_Commutation.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
uint8_t hall_index[6]={1,5,4,6,2,3};
uint8_t sectorTableOfHall[7]={0,5,3,4,1,0,2};
Motor_Sensor_t strSensor;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void MC_SensorMode_Init(void)
{
    strSensor.ModeEn = SENSOR_MODE;

    strSensor.Hall_A = HALL_A;
    strSensor.Hall_B = HALL_B; 
    strSensor.Hall_C = HALL_C;
    strSensor.hallNow = 1;
    strSensor.hallLast = 1;
    strSensor.HallSector = 1;  
}

void MC_SensorMode_HallChange(void)
{
    uint8_t hallData = 0;
	uint8_t sectorNumOfHall;

    if(HALL_A_IO) 
	{
		hallData |=  strSensor.Hall_A;
	}
	if(HALL_B_IO) 
	{
		hallData |=  strSensor.Hall_B;
	}
	if(HALL_C_IO) 
	{
		hallData |=  strSensor.Hall_C;
	}
	strSensor.hallNow = hallData;
	printf(" %d \n\r",hallData);
}

uint8_t get_hallValue(void)
{
	uint8_t hallData = 0;
	uint8_t sectorNumOfHall;

    if(HALL_A_IO) 
	{
		hallData |=  0x01U << 2;
	}
	if(HALL_B_IO) 
	{
		hallData |=  0x01U << 1;
	}
	if(HALL_C_IO) 
	{
		hallData |=  0x01U << 0;
	}
	return hallData;
}
