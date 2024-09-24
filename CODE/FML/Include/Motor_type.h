
#ifndef MOTOR_TYPE_H 
#define MOTOR_TYPE_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include <stdint.h>
/*-----------------------------------macro------------------------------------*/
#define U8_MAX     ((uint8_t)255)
#define S8_MAX     ((int8_t)127)
#define S8_MIN     ((int8_t)-128)
#define U16_MAX    ((uint16_t)65535u)
#define S16_MAX    ((int16_t)32767)
#define S16_MIN    ((int16_t)-32768)
#define U32_MAX    ((uint32_t)4294967295uL)
#define S32_MAX    ((int32_t)2147483647)
#define S32_MIN    ((int32_t)-2147483648)

#define divSQRT_3	 (int32_t)0x49E6    /* 1/sqrt(3) in q1.15 format=0.5773315*/
//#define SQRT_3     1.732051
#define SQRT3_FACTOR  0xDDB4 /*(1.732051 * 16384 * 2)*/

/*----------------------------------typedef-----------------------------------*/
/** 
  * @brief  Two components stator current type definition 
  */
typedef struct 
{
  int16_t qI_Component1;
  int16_t qI_Component2;
} Curr_Components;

/** 
  * @brief  Two components stator voltage type definition 
  */
typedef struct 
{
  int16_t qV_Component1;
  int16_t qV_Component2;
} Volt_Components;

/** 
  * @brief  Trigonometrical functions type definition 
  */
  typedef struct
  {
    int16_t hCos;
    int16_t hSin;
  } Trig_Components;
/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* MOTOR_TYPE_H */
