#include "ELLEPwm.h"
#include "cc253x.h"

PWMPrivateData_Typedef   PWM_Dat;



//----------------------------------------------------------------//
void fnPWM_InitTimeSet(void)
{
  fnPWM_InitAllChannl();
  
  //-------------------------------
  T3CTL   = 0x24;  // Prescaler divider =1, Int dis, Clear Counter, Free-running 00~FF
  
  T3CCTL0 = 0x1C;  // Int Dis, CMP=100 0 Set;Compare 1, Compare, No Capture
  T3CC0   = 0;
  T3CCTL1 = 0x1C;                
  T3CC1   = 0;

  P1DIR  |= 0xC0;  // P17,P16 OutPut
  P1SEL  |= 0xC0;  // P17,P16 Peripheral Function
  PERCFG |= 0x20;  // Timer3 Alternative 2 Location
  P2SEL  |= 0x20;  // Timer3 Priority
  
  T3CTL  |= 0x10;  // START = 1

  //-------------------------------
  T4CTL   = 0x24;  // Prescaler divider =1, Int dis, Clear Counter, Free-running 00~FF
  
  T4CCTL0 = 0x1C;  // Int Dis, CMP=100 0 Set;Compare 1, Compare, No Capture
  T4CC0   = 0;
  T4CCTL1 = 0x1C;                
  T4CC1   = 0;

  P1DIR  |= 0x03;  // P10,P11 OutPut
  P1SEL  |= 0x03;  // P10,P11 Peripheral Function
  //PERCFG |= 0x10;// Timer4 Alternative 2 Location  
  P2SEL  |= 0x10;  // Timer4 Priority
  
  T4CTL  |= 0x10;  // START = 1
  
  
}

//----------------------------------------------------------------//
void fnPWM_InitAllChannl( void )
{
   PWM_Dat.OprFlag     = 0;    // Clear Operate Flag
   PWM_Dat.ModFlag     = 0;    // Inc Mode

   PWM_Dat.BanFlag     = 0;    // Set Flag
   
   PWM_Dat.Ch1CurVal   = 0;
   PWM_Dat.Ch2CurVal   = 0; 
   PWM_Dat.Ch3CurVal   = 0;  
   PWM_Dat.Ch4CurVal   = 0;  
   
   PWM_Dat.Ch1ObjVal   = 0; 
   PWM_Dat.Ch2ObjVal   = 0; 
   PWM_Dat.Ch3ObjVal   = 0; 
   PWM_Dat.Ch4ObjVal   = 0;   
}

/*
*直接设置pwm，不渐变
*/



void fnPwm_setDirectValue(PwmChannl Channlx, unsigned int Value)
{
  switch( Channlx )
    {
        //===================
        case ENUM_PWM_CHANNL_1:    
             PWM_Dat.Ch1CurVal = Value;
			 PWM_Dat.Ch1ObjVal = Value;
			 PWM_Dat.OprFlag &= ~MAC_PWM_CH1_OPERATE_FLAG;
             break;
        //===================
        case ENUM_PWM_CHANNL_2:
             PWM_Dat.Ch2CurVal = Value;
			 PWM_Dat.Ch2ObjVal = Value;
			 PWM_Dat.OprFlag &= ~MAC_PWM_CH2_OPERATE_FLAG;
			 break;
        //===================
        case ENUM_PWM_CHANNL_3:
             PWM_Dat.Ch3CurVal = Value;
			 PWM_Dat.Ch3ObjVal = Value;
			 PWM_Dat.OprFlag &= ~MAC_PWM_CH3_OPERATE_FLAG;
             break;
        //=================== 
        case ENUM_PWM_CHANNL_4:
             PWM_Dat.Ch4CurVal = Value;
			 PWM_Dat.Ch4ObjVal = Value;
			 PWM_Dat.OprFlag &= ~MAC_PWM_CH4_OPERATE_FLAG;
			 break;
        //===================
        default:
             return;
             break;
    }	
  fnPWM_SetPwmValue( Channlx, Value );
}


// White  P10  Timer4 CH0   PWM_CHANNL_1
// Red    P11  Timer4 CH1   PWM_CHANNL_2
// Blue   P16  Timer3 CH0   PWM_CHANNL_3
// Green  P17  Timer3 CH1   PWM_CHANNL_4
void fnPWM_SetPwmValue( PwmChannl Channlx, unsigned int Value )    
{
  unsigned int tmp;
  
  if( Value > 10 )
  	{
      tmp = (Value-2)/2;
    }
  else
  	{
      tmp = Value/2;
    }
  
  switch( Channlx )
    {
      //===================
      case ENUM_PWM_CHANNL_1:                   
           if( tmp > 0 )
             {
               T4CCTL0 = 0x24;                 
               T4CC0   = tmp;
             }
           else
             {
               T4CCTL0 = 0x1c; 
               T4CC0   = 0;
             }        
           break;
      //===================     
      case ENUM_PWM_CHANNL_2:                   
           if( tmp > 0 )
             {
               T4CCTL1 = 0x24;                
               T4CC1   = tmp;
             }
           else
             {
               T4CCTL1 = 0x1c;
               T4CC1   = 0;
             }
           break;
      //===================     
      case ENUM_PWM_CHANNL_4: 
           if( tmp > 0 )
             {
               T3CCTL0 = 0x24;                 
               T3CC0   = tmp;
             }
           else
             {
               T3CCTL0 = 0x1c; 
               T3CC0   =0;
             }  
           break;
      //=================== 
      case ENUM_PWM_CHANNL_3:                   
           if( tmp > 0 )
             {
               T3CCTL1 = 0x24;                
               T3CC1   = tmp;
             }
           else
             {
               T3CCTL1 = 0x1c; 
               T3CC1   = 0;
             }
           break;
      //===================
	  default:
           return;
		   break;
   }
}


void fnPWM_SetChannlxValue( PwmChannl Channlx, unsigned int Value )
{
  unsigned int  LastValue;
  unsigned int  TmpFlg;
  PWM_Dat.BanFlag = 1;
  
  switch( Channlx )
  	{
      case ENUM_PWM_CHANNL_1:   
           TmpFlg            = MAC_PWM_CH1_MODE_FLAG;
           LastValue         = PWM_Dat.Ch1CurVal;
           PWM_Dat.Ch1ObjVal = Value;
           break;
      case ENUM_PWM_CHANNL_2:
           TmpFlg            = MAC_PWM_CH2_MODE_FLAG; 
           LastValue         = PWM_Dat.Ch2CurVal;
           PWM_Dat.Ch2ObjVal = Value;
           break;
      case ENUM_PWM_CHANNL_3:
	       TmpFlg            = MAC_PWM_CH3_MODE_FLAG;
           LastValue         = PWM_Dat.Ch3CurVal;
           PWM_Dat.Ch3ObjVal = Value;        
           break;
      case ENUM_PWM_CHANNL_4:
	       TmpFlg            = MAC_PWM_CH4_MODE_FLAG;
           LastValue         = PWM_Dat.Ch4CurVal;  
           PWM_Dat.Ch4ObjVal = Value;
           break;
	  default:
           return;
  	}

  //=====
  if( LastValue == Value )
    {
      switch( Channlx )
        {
          case ENUM_PWM_CHANNL_1:    
               PWM_Dat.OprFlag &= ~MAC_PWM_CH1_OPERATE_FLAG;
               break;
          case ENUM_PWM_CHANNL_2:
               PWM_Dat.OprFlag &= ~MAC_PWM_CH2_OPERATE_FLAG;
               break;
          case ENUM_PWM_CHANNL_3:
               PWM_Dat.OprFlag &= ~MAC_PWM_CH3_OPERATE_FLAG;
               break;
          case ENUM_PWM_CHANNL_4:
               PWM_Dat.OprFlag &= ~MAC_PWM_CH4_OPERATE_FLAG;
               break;
          default:
               break;
        }
      PWM_Dat.BanFlag = 0;
      return;
    }
  
  // Set Change Mode
  if( LastValue>Value ) // Dec -> 1
    {
      PWM_Dat.ModFlag |=  TmpFlg;  // Dec
    }
  else 
    {
      PWM_Dat.ModFlag &= ~TmpFlg;  // Add
    }

  // Trigger 
  PWM_Dat.OprFlag  |= TmpFlg; 
  PWM_Dat.OprFlag  &= 0x0F;
  
  PWM_Dat.BanFlag   = 0;
}


#define _____________________________Line


#define MAC_PWM_CHANGE_GRAD      2
#define MAC_PWM_GRAD_LOCKED(x)   {if(x>MAC_PWM_CHANGE_GRAD){x=MAC_PWM_CHANGE_GRAD;}}


//=========================================Channl1
void fnPWM_TimerPollCh1(void)
{
  unsigned int TmpVal;

  if( PWM_Dat.OprFlag & MAC_PWM_CH1_OPERATE_FLAG )
    {
      if( PWM_Dat.ModFlag & MAC_PWM_CH1_MODE_FLAG ) // Dec
        {
          TmpVal = PWM_Dat.Ch1CurVal - PWM_Dat.Ch1ObjVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch1CurVal -= TmpVal;
        }
      else                                          
        {
          TmpVal = PWM_Dat.Ch1ObjVal - PWM_Dat.Ch1CurVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch1CurVal += TmpVal;
        }
      
      fnPWM_SetPwmValue( ENUM_PWM_CHANNL_1, PWM_Dat.Ch1CurVal );
      if( PWM_Dat.Ch1CurVal == PWM_Dat.Ch1ObjVal )
        { 
          PWM_Dat.OprFlag &= ~MAC_PWM_CH1_OPERATE_FLAG;
        } 
    }
}

//=========================================Channl2
void fnPWM_TimerPollCh2(void)
{
  unsigned int TmpVal;

  if( PWM_Dat.OprFlag & MAC_PWM_CH2_OPERATE_FLAG )
  	{
  	  if( PWM_Dat.ModFlag & MAC_PWM_CH2_MODE_FLAG ) // Dec
  	  	{
          TmpVal = PWM_Dat.Ch2CurVal - PWM_Dat.Ch2ObjVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch2CurVal -= TmpVal;
  	  	}
	  else
	    {
          TmpVal = PWM_Dat.Ch2ObjVal - PWM_Dat.Ch2CurVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch2CurVal += TmpVal;
	    }
	  fnPWM_SetPwmValue( ENUM_PWM_CHANNL_2, PWM_Dat.Ch2CurVal );
	  if( PWM_Dat.Ch2CurVal == PWM_Dat.Ch2ObjVal )
	    { 
	      PWM_Dat.OprFlag &= ~MAC_PWM_CH2_OPERATE_FLAG;
	    } 
  	}
}
//=========================================Channl3
void fnPWM_TimerPollCh3(void)
{
  unsigned int TmpVal;
  
  if( PWM_Dat.OprFlag & MAC_PWM_CH3_OPERATE_FLAG )
  	{
  	  if( PWM_Dat.ModFlag & MAC_PWM_CH3_MODE_FLAG ) // Dec
  	  	{
          TmpVal = PWM_Dat.Ch3CurVal - PWM_Dat.Ch3ObjVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch3CurVal -= TmpVal;
  	    }
      else
	    {
          TmpVal = PWM_Dat.Ch3ObjVal - PWM_Dat.Ch3CurVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch3CurVal += TmpVal;
	    }
	  fnPWM_SetPwmValue( ENUM_PWM_CHANNL_3, PWM_Dat.Ch3CurVal );
	  if( PWM_Dat.Ch3CurVal == PWM_Dat.Ch3ObjVal )
	    { 
	      PWM_Dat.OprFlag &= ~MAC_PWM_CH3_OPERATE_FLAG;
	    } 
  	}
}
//=========================================Channl4
void fnPWM_TimerPollCh4(void)
{
  unsigned int TmpVal;

  if( PWM_Dat.OprFlag & MAC_PWM_CH4_OPERATE_FLAG )
  	{
  	  if( PWM_Dat.ModFlag & MAC_PWM_CH4_MODE_FLAG ) // Dec
  	    {
          TmpVal = PWM_Dat.Ch4CurVal - PWM_Dat.Ch4ObjVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch4CurVal -= TmpVal;
  	    }
	  else
	    {
          TmpVal = PWM_Dat.Ch4ObjVal - PWM_Dat.Ch4CurVal;
          MAC_PWM_GRAD_LOCKED(TmpVal);
          PWM_Dat.Ch4CurVal += TmpVal;
	    }
	  fnPWM_SetPwmValue( ENUM_PWM_CHANNL_4, PWM_Dat.Ch4CurVal );
	  if( PWM_Dat.Ch4CurVal == PWM_Dat.Ch4ObjVal )
	    { 
	      PWM_Dat.OprFlag &= ~MAC_PWM_CH4_OPERATE_FLAG;
	    } 
  	}
}
                                                 
//=========================================Polling 
void fnPWM_TimerPollHandler( void )
{
  if( 0 == PWM_Dat.OprFlag )
    {
      return;
    }
  
  if( 1 == PWM_Dat.BanFlag )
    {
      return;
    }

  fnPWM_TimerPollCh1();
  fnPWM_TimerPollCh2();
  fnPWM_TimerPollCh3();
  fnPWM_TimerPollCh4();
  
  
}

