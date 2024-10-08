#ifndef ADC_CONFIG_H 
#define ADC_CONFIG_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "Hardware_drivers.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/
typedef struct 
{
    int16_t IBusOffset;

	int16_t VoltageU;				                                
	int16_t VoltageV;				                               
	int16_t VoltageW;				                         
	int16_t VoltageBUS;	

    int16_t CurrentU;				                                
	int16_t CurrentV;		
    int16_t CurrentW;		                              
	int16_t CurrentBUS;			                                                            
}ADCData_TypeDef;

extern ADCData_TypeDef ADCData;
/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void ADC_Init(void);
void ADCDataInit(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* ADC_CONFIG_H */
