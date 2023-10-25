/*
 * Timer_prog.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "Timer_register.h"
#include "Timer_private.h"
#include "Timer_conf.h"
#include "Timer_int.h"

void (*Timer0_Overflow_CallBack)(void) ; /**pointer to function to set call back of Timer0_Overflow_ISR*/
void (*Timer2_Overflow_CallBack)(void) ; /**pointer to function to set call back of Timer2_Overflow_ISR*/
void (*Timer0_CTC_CallBack)     (void) ; /**pointer to function to set call back of Timer0_CTC_ISR     */
void (*Timer2_CTC_CallBack)     (void) ; /**pointer to function to set call back of Timer2_CTC_ISR     */

/*set counter to tack action*/
u32 G_u32IntervalCount = 0 ;

void MTimer_voidInt (void)
{
	
	/** Enable global interrupt flag */
	    SET_BIT(SREG, I_BIT);
		
        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/
	#if   TIMER0 == ENABLE0
	    /**set prescaller of ADC clk*/
	    #if   TIMER0_PRESCALER == CLK_PS_1          /**clk = 8MHZ    */	
		    SET_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_8          /**clk = 1MHZ    */	
			CLR_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_64         /**clk = 125KHZ  */	
		    SET_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_256        /**clk = 31.25KHZ*/
            CLR_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;		
	    #elif TIMER0_PRESCALER == CLK_PS_1024       /**clk = 7.8KHZ  */	
		    SET_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == EXIT_FALLING_EDGE /**external clk source on T0 pin (clock on faling edge)*/	
	        CLR_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
		#elif TIMER0_PRESCALER == EXIT_RISING_EDGE  /**external clk source on T0 pin (clock on rising edge)*/
		    SET_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
		#else 
			#error "select correct options of TIMER0_PRESCALER"
		#endif
	
		/**Timer/counter0 mode*/
		#if   TIMER0_MODE == NORMAL_MODE
		    CLR_BIT(TCCR0 , WGM00) ;/*Normal mode (over flow mode)*/
		    CLR_BIT(TCCR0 , WGM01) ;
			SET_BIT(TIMSK , TOIE0);/*Enable interrupt of over flow mode*/
		#elif TIMER0_MODE == PWM_PHASE_CORRECT_MODE
		    SET_BIT(TCCR0 , WGM00) ;/*phase correct mode*/
		    CLR_BIT(TCCR0 , WGM01) ;
		#elif TIMER0_MODE == COMPARE_MATCH_MODE
		    CLR_BIT(TCCR0 , WGM00) ;/*output compare match mode*/
		    SET_BIT(TCCR0 , WGM01) ;
			SET_BIT(TIMSK , OCIE0);/*Enable interrupt of compare match mode*/
		#elif TIMER0_MODE == FAST_PWM_MODE
		    SET_BIT(TCCR0 , WGM00) ;/*fast pwm*/
		    SET_BIT(TCCR0 , WGM01) ;
			
		#else 
			#error "select correct mode of TIMER0_MODE"
		#endif
		
	#elif TIMER0 == DISABLE0
	/** NO clk source (Timer0 stopped) */
	    CLR_BIT(TCCR0 , CS00) ;
	    CLR_BIT(TCCR0 , CS01) ;
	    CLR_BIT(TCCR0 , CS02) ;
	#else 
		#error "TIMER0 must be ENABLE0 or DISABLE0"
    #endif
	
        /****************************************************************/
        /*                         TIMER2                               */
        /****************************************************************/	
	#if   TIMER2 == ENABLE2
	#elif TIMER2 == DISABLE2
	#else 
		#error "TIMER2 must be ENABLE2 or DISABLE2"
    #endif
	
        /****************************************************************/
        /*                         TIMER1                               */
        /****************************************************************/	
	#if   TIMER1 == ENABLE1
	#elif TIMER1 == DISABLE1
	/** NO clk source (Timer0 stopped) */
	    CLR_BIT(TCCR2 , CS20) ;
	    CLR_BIT(TCCR2 , CS21) ;
	    CLR_BIT(TCCR2 , CS22) ;
	#else 
		#error "TIMER1 must be ENABLE1 or DISABLE1"
	#endif
}

void MTimer_voidSetDisiredTime (u8 A_u8TimerID , f32 A_f32DisiredTime , void (*A_fptr)(void) )
{
	/*switch (A_u8TimerID)
	{
		case TIMER0 :*/
		    #if   TIMER0_MODE == NORMAL_MODE  
		        f32 L_f32OverFlowTime      = 256 ;
	            f32 L_f32OverFlowCount      = 0 ;
	            u16  L_u16NumberOfTimerCount = 256 ;
	            u16  L_u16PreloadValue       = 0 ;
				
	            L_f32OverFlowTime  = L_f32OverFlowTime * TIMER0_PRESCALER ;
                L_f32OverFlowTime  = L_f32OverFlowTime / CLOK_SYSTEM ;
				L_f32OverFlowCount = A_f32DisiredTime / L_f32OverFlowTime ;
				Timer0_Overflow_CallBack = A_fptr ;
				if (L_f32OverFlowCount < 1.0)
				{
					L_u16NumberOfTimerCount = L_u16NumberOfTimerCount * A_f32DisiredTime ;
					L_u16NumberOfTimerCount = L_u16NumberOfTimerCount / L_f32OverFlowTime ;
					L_u16PreloadValue       = 256 - L_u16NumberOfTimerCount ;
					TCNT0 = L_u16PreloadValue ;
					G_u32IntervalCount = 1 ;
				}
				else
				{
					G_u32IntervalCount = (u32)L_f32OverFlowCount ;
					if (L_f32OverFlowCount - (u32)L_f32OverFlowCount != 0.0)
					{
						G_u32IntervalCount ++ ;
					}
				}
			#elif TIMER0_MODE == COMPARE_MATCH_MODE
			#else 
				#error "in MTimer_voidSetDisiredTime function: TIMER0_MODE must be NORMAL_MODE or COMPARE_MATCH_MODE"
	        #endif
	//}
	
	
}

/*ISR of Timer0 over flow*/
void __vector_11(void)__attribute__((signal))__attribute__((interrupt));
void __vector_11(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32IntervalCount)
	{
		if(Timer0_Overflow_CallBack != NULL)
		{
			Timer0_Overflow_CallBack();
			LS_u32Counter = 0;
		}
	}
}