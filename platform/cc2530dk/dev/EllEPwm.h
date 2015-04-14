#ifndef __DIR_PWM_H
#define __DIR_PWM_H




typedef enum
{
   ENUM_PWM_CHANNL_1 = 1,
   ENUM_PWM_CHANNL_2 = 2, 
   ENUM_PWM_CHANNL_3 = 3, 
   ENUM_PWM_CHANNL_4 = 4  
}PwmChannl;

typedef struct
{
  unsigned char OprFlag;  // Channel BanFlag
  unsigned char ModFlag;  // INC DEC
  unsigned char BanFlag;
  
  unsigned int  Ch1CurVal;
  unsigned int  Ch2CurVal;
  unsigned int  Ch3CurVal;
  unsigned int  Ch4CurVal;

  unsigned int  Ch1ObjVal;
  unsigned int  Ch2ObjVal;
  unsigned int  Ch3ObjVal;
  unsigned int  Ch4ObjVal;

}PWMPrivateData_Typedef;

#define  MAC_PWD_ABS(x)   x>0?x:-x


#define  MAC_PWM_BIT(x)   (0x01<<x)


#define  MAC_PWM_CH1_OPERATE_FLAG   MAC_PWM_BIT(0)
#define  MAC_PWM_CH2_OPERATE_FLAG   MAC_PWM_BIT(1)
#define  MAC_PWM_CH3_OPERATE_FLAG   MAC_PWM_BIT(2)
#define  MAC_PWM_CH4_OPERATE_FLAG   MAC_PWM_BIT(3)


#define  MAC_PWM_CH1_MODE_FLAG      MAC_PWM_BIT(0)
#define  MAC_PWM_CH2_MODE_FLAG      MAC_PWM_BIT(1)
#define  MAC_PWM_CH3_MODE_FLAG      MAC_PWM_BIT(2)
#define  MAC_PWM_CH4_MODE_FLAG      MAC_PWM_BIT(3)


#define  MAC_PWM_INC_MODE  0
#define  MAC_PWM_DEC_MODE  1

#define MAC_PWM_INIT_STEP_TIME_IN_MS       2  // MS

void progressPwmLight(void);
void fnPWM_InitAllChannl( void );
void fnPwm_setDirectValue(PwmChannl Channlx, unsigned int Value);
void fnPWM_SetPwmValue( PwmChannl Channlx, unsigned int Value );
void fnPWM_SetChannlxValue( PwmChannl Channlx, unsigned int Value );
void fnPWM_TimerPollHandler( void );

void fnPWM_InitTimeSet(void);


#endif

