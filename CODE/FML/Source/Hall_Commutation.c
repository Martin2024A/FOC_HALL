
/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/
/*旋转方向定义*/
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
高频任务：ADC采样完成，触发中断。FOC
中频任务：更新计算
低频任务：霍尔捕获中断
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
 * @brief   更新电机的电角速度和机械角速度，将整型速度值/每foc执行周期转化为rad/s
 * @param   dpp 整型，指的是整型速度值/每foc执行周期
 * @param   hall 霍尔传感器对象
 * @return
 */
float  hall_get_Speed(HALL_Struct* hall)
{
    /*dpp为整型速度值/每foc执行周期 ，需要后期转化为rad/s*/
    /*所以高频任务的执行周期和65535和2PI需要结合实际弄出个乘积因子完成单位转化过程*/
    static float K=(float)(N2_PI/65536/(FOC_PERIOD/1000000.0f));
	
    hall->omega_inter=((float)(K*hall->dpp));
	
    return hall->omega_inter;
}
/**
 * @brief   插值法电角度估算函数(用于FOC高频中断任务中)
 * @param   hall 霍尔传感器指针
 * @funtion 实现了插值法捕获速度值;该方式使用-65536~65536表示-2pi到2pi
 */
float hall_positionEst(HALL_Struct *hall)
{
      static float theta_k=N2_PI/65536;

      hall->refer_theta+=hall->dpp;//<refer_theta就是文中的θref(在代码中仅有整型形式)
      if(hall->refer_theta>65536L)
      {
          hall->refer_theta-=65536L;
      }
      else if(hall->refer_theta<0)
      {
          hall->refer_theta+=65536L;
      }
      hall->theta+=(hall->dpp+hall->comp_dpp);//<就是文中的θuse的整型形式
      if(hall->theta>65536L)
     {
         hall->theta-=65536L;
     }
     else if(hall->theta<0)
     {
         hall->theta+=65536L;
     }
		 
		 hall->theta_inter=(float)(hall->theta*theta_k);//<theta_inter插值法估算的电角度，就是文中的θuse浮点形式
     return hall->theta_inter;
}


/**
 * @brief            霍尔捕获(中断)低频任务（频率不定，所以在本函数还对霍尔中断频率做了计算）
 * @param    htim    霍尔中断捕获所使用的定时器指针
 * @function         实现了插值法捕获速度值;该方式使用-65536~65536表示-2pi到2pi
 *	                 方案采用扇区强制校准+插值补偿	
 *                   本部分函数实现了扇区角度强制校准+中间速度缓存变量计算+平均速度计算
                    
                     此处以120°电角度放置的霍尔位置传感器为例
					 LF：low frequency低频
 * @warnings         ！！！注意：本函数配合中频任务共同运行才能完成一次完整的速度估计
                     所以，完整电角度估算与速度估算流程是共同混杂在foc高频中断+速度更新中频任务+霍尔中断低频任务中的
 */
#define TIM_HALL_CK_INT				(48000000UL)          //用户自定义，指霍尔捕获所用的定时器外设主频，F4芯片一般除TIM1/TIM8，其余为84M
#define TIM_HALL_REFER_CAP          (25000UL)


#define S16_60_PHASE_SHIFT       	(10923UL)
#define S16_120_PHASE_SHIFT      	(21845UL)
#define S16_180_PHASE_SHIFT      	(32768UL)
#define S16_240_PHASE_SHIFT      	(43691UL)
#define S16_300_PHASE_SHIFT      	(54613UL)

#define HALL_FW                  	(+1L)                   //霍尔周期正转
#define HALL_RV                  	(-1L)                   //霍尔周期反转
///<120°电角度放置时的霍尔真值
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
    
    //<产生霍尔跳变，必定同时产生更新标记(先检测)和捕获标记(后检测)
    //<堵转只产生更新标记，不会产生捕获标记，因为霍尔真值没有变化
  /*
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_UPDATE))
	{
		///<没有霍尔跳变却发生了更新中断，说明速度太慢或堵转，计数器溢出更新
       if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1)!= SET)
       {
			hall->overcount++;
			if(hall->overcount>500U)//<用户自定义堵转时间间隔，这里选500.但不一定非要500，具体情况具体分析，读者根据自己的需求来选堵转阈值。
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
				motor1.state=MOTOR_STOP;//<电机已经堵转，初始化所有值并标记当前为电机停运状态
			}
       }	
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_UPDATE);
	}
  */
	///<发生了霍尔跳变，捕获当前霍尔真值，并进行相应操作
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_CC1))
	{
		hall->last_state=hall->state;//<保存上次的霍尔真值
    hall->state=Get_HallValue();
		
    	/**********************计算溢出期间的计数值 ************************/
   		/*************************CCR1捕获到值 ****************************/
		ccr1=htim->Instance->CCR1;
    hall->cap=(hall->overcount*0x10000L)+ccr1;
   		/********因为霍尔捕获存在硬件误差，根据STM32的定时器更新特性做速度适应处理********/
   		/*当然不做预分频更新处理，也不影响算法运行，若读者技术水平较弱，入门还请略过此步骤否则会适得其反*/
   		/*****笔者的目的是为了在不同速度下，其预分频下捕捉到的CCRx值都在25000左右(满值为65535嘛)*****/
   		/*这个时候呢，需要根据不同速度，动态调整预分频值，使得CCRx稳定在一个较大值，使硬件误差最小化*/
   		/*****************************上文图片中默认配置了预分频为128-1*****************************/
   		/*因为STM32的预分频值更新使用了影子功能，预分频更新值与计算f_HALL实际用到的分频值，还请参考笔者代码*/
    	/*
      if(hall->overcount>0)     ///<速度过慢,但预分频值过低
    	{
			hall->prescaler=htim->Instance->PSC+1;
			if(hall->RatioInc!=0) ///<RatioInc预分频值增加标志位
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
    	else                       ///<速度过快,但预分频值过高
    	{
			if(hall->RatioDec!=0) ///<RatioDec预分频值减少标志位
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
    /*******************************!!!校准********************************/
    ///正反转相同位置，同一霍尔真值，但电角度实际是相差60°的
    ///offset_theta就是上文中提到的γ角
	switch (hall->state)
    {
      case HALL_5:
      {
        if(hall->last_state==HALL_1)
        {
          	hall->direction=HALL_FW;//<refer_theta就是上文的θref
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
    	/*****************************校准 End********************************/
		
		/*************************电角度估算参数迭代 ****************************/
		if(hall->startup!=0)
		{
			//电机启动期间速度计算（启动时候六个扇区都没有填满值，启动前6次有多少个数据就除多少个）
			hall->dpp_sum-=hall->buffer[hall->buffer_index];
			hall->f_hall=(TIM_HALL_CK_INT/(hall->prescaler*hall->cap));
			dpp=(10923UL*hall->f_hall/hall->f_foc)*hall->direction;///<10923UL是60°弧度的整型定标
			hall->buffer[hall->buffer_index]=dpp;
			hall->dpp_sum+=hall->buffer[hall->buffer_index];
			hall->buffer_index++;
			hall->avg_dpp=(hall->dpp_sum/hall->buffer_index);	
			if(hall->buffer_index>=WBuffer_MAX_SIZE)//<WBuffer_MAX_SIZE此处为6
			{
				hall->startup=0;//<清除电机启动标志位
				hall->buffer_index=0;
			}
		}
		else
		{
			///滑动均值滤波（完成启动，缓存区都有6个数据，往后都除以6求平均）
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
        /*************************电角度估算参数迭代 End************************/
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_CC1);
	}
}


/**
 * @brief            速度更新中频任务（频率1k，确保速度更新大于速度环，速度更新频率一般1kHz）
 * @param    htim    速度更新所使用的定时器指针
 * @function         这里配合foc高频中断+霍尔中断捕获实现估算插值补偿               
 *                   MF：Moderate frequency中频
 

 * @warnings         ！！！注意：本函数配合中频任务共同运行才能完成一次完整的速度估计
                     所以，完整电角度估算与速度估算流程是共同混杂在foc任务+速度更新中频任务+霍尔中断低频任务中的
 */
void speed_updateMF_IT(HALL_Struct *hall)
{
	static int32_t  n=(int32_t)(SPEED_PERIOD/FOC_PERIOD);///<就是公式中的n
	if(__HAL_TIM_GET_FLAG(htim,TIM_FLAG_UPDATE))
	{
		hall->dpp_2=hall->dpp_1;
    hall->dpp_1=hall->avg_dpp;
    hall->a_dpp=hall->dpp_1-hall->dpp_2;
    hall->dpp = hall->dpp_1+hall->a_dpp;
    hall->delta_theta = hall->refer_theta - hall->theta;
		
		//5462为30°的整型值，65536为2PI
		//当电机实际的角度追踪值与FOC所用的角度值差30°时不可接受
		//故当偏差大于30°时强制让它为追踪值；
		if(hall->delta_theta>5462)
		{
			hall->theta=hall->refer_theta;//<refer_theta就是上文的θref
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
 * @brief            FOC高频中断运行流程（至少8K，这里选取10K执行频率）
 * @param            电机FOC流程对象结构体
 * @description      电机的状态机用户可自行定义，这里从简
 *                   HF：High frequency高频
 */
void foc_processHF_IT(HALL_Struct *hall)
{
		static float Rv_U=0,Rv_V=0,Rv_W=0;                //<采样电阻电压
		static float current_U=0,current_V=0,current_W=0; //<三电阻法，相电流存储变量
		static float speedP=(float)(1.0f/4);              //<乘积因子，电角速度=极对数*机械角速度
		
		if(__HAL_ADC_GET_FLAG(foc->adc_motor_output.hadc,ADC_FLAG_JEOC))
		{
			/*********电流采样(入门秘法：不分扇区情况，按两电阻法直接暴力采)*******/

      
					/*********二选一，根据需求注释掉就可，推荐PLL法********/
					//****************插值法****************//
					hall_get_Speed(hall);//<插值法估算电角速度rad/s
					hall_positionEst(hall);//<插值法估算角度
					//***********锁相环PLL法***************//
					// hall_get_Speed(hall);//<插值法获取电角速度rad/s
					// foc->angle_result.electrical_angle=hall_pll_filter(&hall1);


					//****机械角速度计算*****//
					foc->speed_result.eleSpeed=hall->omega_inter;//<插值法或锁相环法中的估算电角速度都可以带入(推荐插值法速度),单位rad/s
			}
		__HAL_ADC_CLEAR_FLAG(foc->adc_motor_output.hadc,ADC_FLAG_JEOC);
	}