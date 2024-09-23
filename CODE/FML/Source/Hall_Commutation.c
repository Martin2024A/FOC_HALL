
/*----------------------------------include-----------------------------------*/
#include "Myproject.h"
/*-----------------------------------macro------------------------------------*/
/*��ת������*/
#define 	CW				 									(0)
#define 	CCW													(1)
#define   FRSet                       (CW)    		
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
uint8_t hall_index[6]={1,5,4,6,2,3};
uint8_t sectorTableOfHall[7]={0,5,3,4,1,0,2};
Motor_Sensor_t strSensor;
/*-------------------------------------os-------------------------------------*/
HALL_Struct   Hall1 = {0};
/*----------------------------------function----------------------------------*/
/*
��Ƶ����ADC������ɣ������жϡ�FOC
��Ƶ���񣺸��¼���
��Ƶ���񣺻��������ж�
*/

uint8_t Get_HallValue(void)
{
	uint8_t hallData = 0;

    if(HALL_A_IO) 
	{
		hallData |=  0x04;
	}
	if(HALL_B_IO) 
	{
		hallData |=  0x02;
	}
	if(HALL_C_IO) 
	{
		hallData |=  0x01;
	}
	return hallData;
}

/**
 * @brief   ���µ���ĵ���ٶȺͻ�е���ٶȣ��������ٶ�ֵ/ÿfocִ������ת��Ϊrad/s
 * @param   dpp ���ͣ�ָ���������ٶ�ֵ/ÿfocִ������
 * @param   hall ��������������
 * @return
 */
float  hall_get_Speed(HALL_Struct* hall)
{
    /*dppΪ�����ٶ�ֵ/ÿfocִ������ ����Ҫ����ת��Ϊrad/s*/
    /*���Ը�Ƶ�����ִ�����ں�65535��2PI��Ҫ���ʵ��Ū�����˻�������ɵ�λת������*/
    static float K=(float)(N2_PI/65536/(FOC_PERIOD/1000000.0f));
	
    hall->omega_inter=((float)(K*hall->dpp));
	
    return hall->omega_inter;
}
/**
 * @brief   ��ֵ����Ƕȹ��㺯��(����FOC��Ƶ�ж�������)
 * @param   hall ����������ָ��
 * @funtion ʵ���˲�ֵ�������ٶ�ֵ;�÷�ʽʹ��-65536~65536��ʾ-2pi��2pi
 */
float hall_positionEst(HALL_Struct *hall)
{
      static float theta_k=N2_PI/65536;

      hall->refer_theta+=hall->dpp;//<refer_theta�������еĦ�ref(�ڴ����н���������ʽ)
      if(hall->refer_theta>65536L)
      {
          hall->refer_theta-=65536L;
      }
      else if(hall->refer_theta<0)
      {
          hall->refer_theta+=65536L;
      }
      hall->theta+=(hall->dpp+hall->comp_dpp);//<�������еĦ�use��������ʽ
      if(hall->theta>65536L)
     {
         hall->theta-=65536L;
     }
     else if(hall->theta<0)
     {
         hall->theta+=65536L;
     }
		 
		 hall->theta_inter=(float)(hall->theta*theta_k);//<theta_inter��ֵ������ĵ�Ƕȣ��������еĦ�use������ʽ
     return hall->theta_inter;
}


/**
 * @brief            ��������(�ж�)��Ƶ����Ƶ�ʲ����������ڱ��������Ի����ж�Ƶ�����˼��㣩
 * @param    htim    �����жϲ�����ʹ�õĶ�ʱ��ָ��
 * @function         ʵ���˲�ֵ�������ٶ�ֵ;�÷�ʽʹ��-65536~65536��ʾ-2pi��2pi
 *	                 ������������ǿ��У׼+��ֵ����	
 *                   �����ֺ���ʵ���������Ƕ�ǿ��У׼+�м��ٶȻ����������+ƽ���ٶȼ���
                    
                     �˴���120���Ƕȷ��õĻ���λ�ô�����Ϊ��
					 LF��low frequency��Ƶ
 * @warnings         ������ע�⣺�����������Ƶ����ͬ���в������һ���������ٶȹ���
                     ���ԣ�������Ƕȹ������ٶȹ��������ǹ�ͬ������foc��Ƶ�ж�+�ٶȸ�����Ƶ����+�����жϵ�Ƶ�����е�
 */
#define TIM_HALL_CK_INT				(48000000UL)          //�û��Զ��壬ָ�����������õĶ�ʱ��������Ƶ��F4оƬһ���TIM1/TIM8������Ϊ84M
#define TIM_HALL_REFER_CAP          (25000UL)


#define S16_60_PHASE_SHIFT       	(10923UL)
#define S16_120_PHASE_SHIFT      	(21845UL)
#define S16_180_PHASE_SHIFT      	(32768UL)
#define S16_240_PHASE_SHIFT      	(43691UL)
#define S16_300_PHASE_SHIFT      	(54613UL)

#define HALL_FW                  	(+1L)                   //����������ת
#define HALL_RV                  	(-1L)                   //�������ڷ�ת
///<120���Ƕȷ���ʱ�Ļ�����ֵ
#define HALL_5                  	(5UL)
#define HALL_1                  	(1UL)
#define HALL_3                  	(3UL)
#define HALL_2                  	(2UL)
#define HALL_6                  	(6UL)
#define HALL_4                  	(4UL)
    

void hall_processLF_IT(HALL_Struct *hall)
{
	static uint16_t  ccr1=0;
  static int32_t   dpp=0;
    
    //<�����������䣬�ض�ͬʱ�������±��(�ȼ��)�Ͳ�����(����)
    //<��תֻ�������±�ǣ�������������ǣ���Ϊ������ֵû�б仯
  /*
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_UPDATE))
	{
		///<û�л�������ȴ�����˸����жϣ�˵���ٶ�̫�����ת���������������
       if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1)!= SET)
       {
			hall->overcount++;
			if(hall->overcount>500U)//<�û��Զ����תʱ����������ѡ500.����һ����Ҫ500���������������������߸����Լ���������ѡ��ת��ֵ��
			{
				hall->locked=1;
				hall->buffer[0]=0;
				hall->buffer[1]=0;
				hall->buffer[2]=0;
				hall->buffer[3]=0;
				hall->buffer[4]=0;
				hall->buffer[5]=0;
				
				hall->dpp_sum=0;
				hall->avg_dpp=0;
				motor1.state=MOTOR_STOP;//<����Ѿ���ת����ʼ������ֵ����ǵ�ǰΪ���ͣ��״̬
			}
       }	
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_UPDATE);
	}
  */
	///<�����˻������䣬����ǰ������ֵ����������Ӧ����
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_CC1))
	{
		hall->last_state=hall->state;//<�����ϴεĻ�����ֵ
    hall->state=Get_HallValue();
		
    	/**********************��������ڼ�ļ���ֵ ************************/
   		/*************************CCR1����ֵ ****************************/
		ccr1=htim->Instance->CCR1;
    hall->cap=(hall->overcount*0x10000L)+ccr1;
   		/********��Ϊ�����������Ӳ��������STM32�Ķ�ʱ�������������ٶ���Ӧ����********/
   		/*��Ȼ����Ԥ��Ƶ���´���Ҳ��Ӱ���㷨���У������߼���ˮƽ���������Ż����Թ��˲��������ʵ��䷴*/
   		/*****���ߵ�Ŀ����Ϊ���ڲ�ͬ�ٶ��£���Ԥ��Ƶ�²�׽����CCRxֵ����25000����(��ֵΪ65535��)*****/
   		/*���ʱ���أ���Ҫ���ݲ�ͬ�ٶȣ���̬����Ԥ��Ƶֵ��ʹ��CCRx�ȶ���һ���ϴ�ֵ��ʹӲ�������С��*/
   		/*****************************����ͼƬ��Ĭ��������Ԥ��ƵΪ128-1*****************************/
   		/*��ΪSTM32��Ԥ��Ƶֵ����ʹ����Ӱ�ӹ��ܣ�Ԥ��Ƶ����ֵ�����f_HALLʵ���õ��ķ�Ƶֵ������ο����ߴ���*/
    	/*
      if(hall->overcount>0)     ///<�ٶȹ���,��Ԥ��Ƶֵ����
    	{
			hall->prescaler=htim->Instance->PSC+1;
			if(hall->RatioInc!=0) ///<RatioIncԤ��Ƶֵ���ӱ�־λ
			{
				hall->overcount=0;
				hall->RatioInc=0;	
			}
			else
		  	{
				if(htim->Instance->PSC<65535)	
				{
					__HAL_TIM_SET_PRESCALER(htim,htim->Instance->PSC+1);
					hall->RatioInc=1;	
				}
			}	
   		 }
    	else                       ///<�ٶȹ���,��Ԥ��Ƶֵ����
    	{
			if(hall->RatioDec!=0) ///<RatioDecԤ��Ƶֵ���ٱ�־λ
			{
				hall->prescaler=htim->Instance->PSC+2;
				hall->RatioDec=0;	
			}
			else
		  	{
				hall->prescaler=htim->Instance->PSC+1;
				if(ccr1<TIM_HALL_REFER_CAP)
				{
					if(htim->Instance->PSC>0)
					{
						__HAL_TIM_SET_PRESCALER(htim,htim->Instance->PSC-1);
						hall->RatioDec=1;	
					}
			    }		
		    }    
   		}
		*/
    /*******************************!!!У׼********************************/
    ///����ת��ͬλ�ã�ͬһ������ֵ������Ƕ�ʵ�������60���
    ///offset_theta�����������ᵽ�Ħý�
	switch (hall->state)
    {
      case HALL_5:
      {
        if(hall->last_state==HALL_1)
        {
          	hall->direction=HALL_FW;//<refer_theta�������ĵĦ�ref
          	hall->refer_theta=hall->offset_theta+S16_240_PHASE_SHIFT;
			      hall->hall_theta=hall->offset_theta+S16_240_PHASE_SHIFT;
        }
        else if(hall->last_state==HALL_4)
        {
          	hall->direction=HALL_RV;
          	hall->refer_theta = hall->offset_theta+S16_300_PHASE_SHIFT;
			      hall->hall_theta= hall->offset_theta+S16_300_PHASE_SHIFT;
        }
		else
			return;
        break;
	  }
      case HALL_1:
      {
        if(hall->last_state==HALL_3)
        {
          	hall->direction=HALL_FW;
          	hall->refer_theta = hall->offset_theta+S16_180_PHASE_SHIFT;
			hall->hall_theta= hall->offset_theta+S16_180_PHASE_SHIFT;
        }
        else if(hall->last_state==HALL_5)
        {
          	hall->direction=HALL_RV;
          	hall->refer_theta = hall->offset_theta+S16_240_PHASE_SHIFT;
			hall->hall_theta=hall->offset_theta+S16_240_PHASE_SHIFT;
        }
		else
			return;
        break;
      }
       case HALL_3:
       {
        if(hall->last_state==HALL_2)
        {
          	hall->direction=HALL_FW;
          	hall->refer_theta = hall->offset_theta+S16_120_PHASE_SHIFT;
			hall->hall_theta= hall->offset_theta+S16_120_PHASE_SHIFT;
        }
        else if(hall->last_state==HALL_1)
        {
          	hall->direction=HALL_RV;
          	hall->refer_theta = hall->offset_theta+S16_180_PHASE_SHIFT;
			hall->hall_theta= hall->offset_theta+S16_180_PHASE_SHIFT;
        }
		else
			return;
        break;
       }
       case HALL_2:
       {
         if(hall->last_state==HALL_6)
         {
           	hall->direction=HALL_FW;
           	hall->refer_theta = hall->offset_theta+S16_60_PHASE_SHIFT;
			hall->hall_theta=hall->offset_theta+S16_60_PHASE_SHIFT;
         }
         else if(hall->last_state==HALL_3)
         {
           	hall->direction=HALL_RV;
           	hall->refer_theta = hall->offset_theta+S16_120_PHASE_SHIFT;
			hall->hall_theta= hall->offset_theta+S16_120_PHASE_SHIFT;
         }
		 else
			return;
         break;
	   }
       case HALL_6:
       {
         if(hall->last_state==HALL_4)
         {
           	hall->direction=HALL_FW;
           	hall->refer_theta = hall->offset_theta;
			hall->hall_theta= hall->offset_theta;
         }
         else if(hall->last_state==HALL_2)
         {
           	hall->direction=HALL_RV;
           	hall->refer_theta = hall->offset_theta+S16_60_PHASE_SHIFT;
			hall->hall_theta= hall->offset_theta+S16_60_PHASE_SHIFT;
         }
		 else
			return;
         break;
       }
        case HALL_4:
        {
           if(hall->last_state==HALL_5)
          {
             	hall->direction=HALL_FW;
             	hall->refer_theta = hall->offset_theta+S16_300_PHASE_SHIFT;
				hall->hall_theta=hall->offset_theta+S16_300_PHASE_SHIFT;
          }
          else if(hall->last_state==HALL_6)
          {
             	hall->direction=HALL_RV;
             	hall->refer_theta = hall->offset_theta;
				hall->hall_theta= hall->offset_theta;
          }
		 else
				return;
         break;
        }
     }
    	/*****************************У׼ End********************************/
		
		/*************************��Ƕȹ���������� ****************************/
		if(hall->startup!=0)
		{
			//��������ڼ��ٶȼ��㣨����ʱ������������û������ֵ������ǰ6���ж��ٸ����ݾͳ����ٸ���
			hall->dpp_sum-=hall->buffer[hall->buffer_index];
			hall->f_hall=(TIM_HALL_CK_INT/(hall->prescaler*hall->cap));
			dpp=(10923UL*hall->f_hall/hall->f_foc)*hall->direction;///<10923UL��60�㻡�ȵ����Ͷ���
			hall->buffer[hall->buffer_index]=dpp;
			hall->dpp_sum+=hall->buffer[hall->buffer_index];
			hall->buffer_index++;
			hall->avg_dpp=(hall->dpp_sum/hall->buffer_index);	
			if(hall->buffer_index>=WBuffer_MAX_SIZE)//<WBuffer_MAX_SIZE�˴�Ϊ6
			{
				hall->startup=0;//<������������־λ
				hall->buffer_index=0;
			}
		}
		else
		{
			///������ֵ�˲����������������������6�����ݣ����󶼳���6��ƽ����
			hall->dpp_sum-=hall->buffer[hall->buffer_index];
			hall->f_hall=(TIM_HALL_CK_INT/(hall->prescaler*hall->cap));
			dpp=(10923UL*hall->f_hall/hall->f_foc)*hall->direction;
			hall->buffer[hall->buffer_index]=dpp;
			hall->dpp_sum+=hall->buffer[hall->buffer_index];
			hall->buffer_index++;
			if(hall->buffer_index>=WBuffer_MAX_SIZE)
			{
				hall->buffer_index=0;
			}
			hall->avg_dpp=(hall->dpp_sum/WBuffer_MAX_SIZE);		
		}
        /*************************��Ƕȹ���������� End************************/
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_CC1);
	}
}


/**
 * @brief            �ٶȸ�����Ƶ����Ƶ��1k��ȷ���ٶȸ��´����ٶȻ����ٶȸ���Ƶ��һ��1kHz��
 * @param    htim    �ٶȸ�����ʹ�õĶ�ʱ��ָ��
 * @function         �������foc��Ƶ�ж�+�����жϲ���ʵ�ֹ����ֵ����               
 *                   MF��Moderate frequency��Ƶ
 

 * @warnings         ������ע�⣺�����������Ƶ����ͬ���в������һ���������ٶȹ���
                     ���ԣ�������Ƕȹ������ٶȹ��������ǹ�ͬ������foc����+�ٶȸ�����Ƶ����+�����жϵ�Ƶ�����е�
 */
void speed_updateMF_IT(HALL_Struct *hall)
{
	static int32_t  n=(int32_t)(SPEED_PERIOD/FOC_PERIOD);///<���ǹ�ʽ�е�n
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_UPDATE))
	{
		hall->dpp_2=hall->dpp_1;
    hall->dpp_1=hall->avg_dpp;
    hall->a_dpp=hall->dpp_1-hall->dpp_2;
    hall->dpp = hall->dpp_1+hall->a_dpp;
    hall->delta_theta = hall->refer_theta - hall->theta;
		
		//5462Ϊ30�������ֵ��65536Ϊ2PI
		//�����ʵ�ʵĽǶ�׷��ֵ��FOC���õĽǶ�ֵ��30��ʱ���ɽ���
		//�ʵ�ƫ�����30��ʱǿ������Ϊ׷��ֵ��
		if(hall->delta_theta>5462)
		{
			hall->theta=hall->refer_theta;//<refer_theta�������ĵĦ�ref
			hall->comp_dpp =(2731 / n);
		}
		else if (hall->delta_theta<-5462)
		{
			hall->theta=hall->refer_theta;
			hall->comp_dpp =(-2731 / n);
		}
		else
		{
			hall->comp_dpp =(hall->delta_theta / n);
		}
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_UPDATE);
	}
}


/**
 * @brief            FOC��Ƶ�ж��������̣�����8K������ѡȡ10Kִ��Ƶ�ʣ�
 * @param            ���FOC���̶���ṹ��
 * @description      �����״̬���û������ж��壬����Ӽ�
 *                   HF��High frequency��Ƶ
 */
void foc_processHF_IT(HALL_Struct *hall)
{
		static float Rv_U=0,Rv_V=0,Rv_W=0;                //<���������ѹ
		static float current_U=0,current_V=0,current_W=0; //<�����跨��������洢����
		static float speedP=(float)(1.0f/4);              //<�˻����ӣ�����ٶ�=������*��е���ٶ�
		
		if(__HAL_ADC_GET_FLAG(foc->adc_motor_output.hadc,ADC_FLAG_JEOC))
		{
			/*********��������(�����ط�����������������������跨ֱ�ӱ�����)*******/

      
					/*********��ѡһ����������ע�͵��Ϳɣ��Ƽ�PLL��********/
					//****************��ֵ��****************//
					hall_get_Speed(hall);//<��ֵ���������ٶ�rad/s
					hall_positionEst(hall);//<��ֵ������Ƕ�
					//***********���໷PLL��***************//
					// hall_get_Speed(hall);//<��ֵ����ȡ����ٶ�rad/s
					// foc->angle_result.electrical_angle=hall_pll_filter(&hall1);


					//****��е���ٶȼ���*****//
					foc->speed_result.eleSpeed=hall->omega_inter;//<��ֵ�������໷���еĹ������ٶȶ����Դ���(�Ƽ���ֵ���ٶ�),��λrad/s
			}
		__HAL_ADC_CLEAR_FLAG(foc->adc_motor_output.hadc,ADC_FLAG_JEOC);
	}