
/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
uint8_t bSector;
int32_t Period = (int32_t)PWM_PERIOD_CYCLE;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/**
  * @brief  It converts input voltage components Valfa and Vbeta into duty cycles
  *         and feed it to the inverter
  * @param  pHandle: handler of the current instance of the PWMC component
  * @param  Valfa_beta: Voltage Components in alfa beta reference frame
  * @retval It returns the code error 'MC_FOC_DURATION' if any, 'MC_NO_ERROR' 
  *         otherwise. These error codes are defined in mc_type.h
  */
void SVPWM_SetPhaseVoltage(Volt_Components Valfa_beta)
{
  int32_t wX, wY, wZ, wUAlpha, wUBeta, wTimePhA, wTimePhB, wTimePhC;


  uint16_t hCntPhA,hCntPhB,hCntPhC;

  //����U��=V�� * Period * SQRT3 * 2
  //U�� = V�� * Period * 2
  wUAlpha = Valfa_beta.qV_Component1 * (int32_t)T_SQRT3;
  wUBeta = -(Valfa_beta.qV_Component2 *(int32_t)Period) * 2;
 
  wX = wUBeta;
  wY = (wUBeta + wUAlpha)/2;
  wZ = (wUBeta - wUAlpha)/2;
  
  /* Sector calculation from wX, wY, wZ */
  if (wY<0)
  {
    if (wZ<0)
    {
      bSector = SECTOR_5;
      wTimePhC = (int32_t)Period/4 + ((wY + wZ)/(int32_t)262144);
      wTimePhA = wTimePhC - wY/131072;
      wTimePhB = wTimePhA - wZ/131072;
    }
    else /* wZ >= 0 */
      if (wX<=0)
      {
        bSector = SECTOR_4;
        wTimePhC = (int32_t)(Period)/4 + ((wX - wZ)/(int32_t)262144);
        wTimePhB = wTimePhC - wX/131072;
        wTimePhA = wTimePhB + wZ/131072;

      }
      else /* wX > 0 */
      {
        bSector = SECTOR_3;
        wTimePhB =  (int32_t)(Period)/4 + ((wY - wX)/(int32_t)262144);
        wTimePhC = wTimePhB + wX/131072;
        wTimePhA = wTimePhC - wY/131072; 
      
      }
  }
  else /* wY > 0 */
  {
    if (wZ>=0)
    {
      bSector = SECTOR_2;
      wTimePhB = (int32_t)(Period)/4 - ((wY + wZ)/(int32_t)262144);
      wTimePhA = wTimePhB + wZ/131072;
      wTimePhC = wTimePhA + wY/131072;  
        //       wTimePhA = 0;
        // wTimePhB = 0;
        // wTimePhC = 0;     
    }
    else /* wZ < 0 */
      if (wX<=0)
      {  
        bSector = SECTOR_6;
        wTimePhA = (int32_t)(Period)/4 + ((wX - wY)/(int32_t)262144);
        wTimePhC = wTimePhA + wY/131072;
        wTimePhB = wTimePhC - wX/131072;
      }
      else /* wX > 0 */
      {
        bSector = SECTOR_1;
        wTimePhA = (int32_t)(Period)/4 + ((wZ - wX)/(int32_t)262144);
        wTimePhB = wTimePhA - wZ/131072;
        wTimePhC = wTimePhB + wX/131072;

      }
  }
  
  hCntPhA = (uint16_t)wTimePhA;
  hCntPhB = (uint16_t)wTimePhB;
  hCntPhC = (uint16_t)wTimePhC;
  
  EPWM_ConfigChannelSymDuty(EPWM0, hCntPhA + DEADTIME);					/*EPWM0ͨ����ռ�ձ� = 25%*/
  EPWM_ConfigChannelSymDuty(EPWM3, hCntPhA - DEADTIME);					/*EPWM0ͨ����ռ�ձ� = 25%*/
	EPWM_ConfigChannelSymDuty(EPWM1, hCntPhB + DEADTIME);					/*EPWM2ͨ����ռ�ձ� = 50%*/	
  EPWM_ConfigChannelSymDuty(EPWM4, hCntPhB - DEADTIME);					/*EPWM2ͨ����ռ�ձ� = 50%*/	
	EPWM_ConfigChannelSymDuty(EPWM2, hCntPhC + DEADTIME);					/*EPWM4ͨ����ռ�ձ� = 75%*/	
  EPWM_ConfigChannelSymDuty(EPWM5, hCntPhC - DEADTIME);					/*EPWM4ͨ����ռ�ձ� = 75%*/	
}


/*------------------------------------test------------------------------------*/
