/*
 * Timer_private.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

/**Status register(SREG) */		
#define I_BIT    7  /**(global interrupt flag)*/

/*Prescaller of clk mc*/
#define CLK_PS_1              1
#define CLK_PS_8              8
#define CLK_PS_64             64
#define CLK_PS_256            256
#define CLK_PS_1024           1024
#define EXIT_FALLING_EDGE     6
#define EXIT_RISING_EDGE      7

/*Modes of timer*/
#define NORMAL_MODE            1
#define PWM_PHASE_CORRECT_MODE 2
#define COMPARE_MATCH_MODE     3
#define FAST_PWM_MODE          4

/*frequancy of mc*/
#define CLOK_SYSTEM 8000000


        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/

/**Timer0/counter0 control register (TCCR0)*/		
#define CS00     0 /*The thee Clock Select bits select the clock source to be used by the Timer/Counter*/
#define CS01     1
#define CS02     2
#define COM00    4 /*Compare Output Mode Bits*/
#define COM01    5
#define WGM01    3 /*Waveform Generation Mode Bits*/
#define WGM00    6
#define FOC0     7 /*Fource Output Compare*/

/**Timer interrupt mask register (TIMSK)*/		
#define TOIE0    0  /*Timer/Counter0 Overflow Interrupt Enable*/
#define OCIE0    1  /*Timer/Counter0 Output Compare Match Interrupt Enable*/

/**Timer interrupt flag register (TIFR)*/		
#define TOV0     0  /*Timer/Counter0 Overflow Flag*/
#define OCF0     1  /*Timer/Counter0 Output Compare Flag*/

/*number of bits of timer 0*/
#define TIMER0_RESOLUTION  8

/*ENABLE/DISABLE TIMER0*/
#define ENABLE0   1  /*ENABLE TIMER0*/
#define DISABLE0  2  /*DISABLE TIMER0*/
		
        /****************************************************************/
        /**                        TIMER2                              **/
        /****************************************************************/

/**Timer2/counter2 control register (TCCR2)*/
#define CS20     0 /*The thee Clock Select bits select the clock source to be used by the Timer/Counter*/
#define CS21     1
#define CS22     2
#define COM20    4 /*Compare Output Mode Bits*/
#define COM21    5
#define WGM21    3 /*Waveform Generation Mode Bits*/
#define WGM20    6
#define FOC2     7 /*Fource Output Compare*/                    

/**Asynchrous status register (ASSR)*/		
#define AS2      3

/**Timer interrupt mask register (TIMSK)*/		
#define TOIE2    6  /*Timer/Counter2 Overflow Interrupt Enable*/
#define OCIE2    7  /*Timer/Counter2 Output Compare Match Interrupt Enable*/

/**Timer interrupt flag register (TIFR)*/		
#define TOV2     6  /*Timer/Counter2 Overflow Flag*/
#define OCF2     7  /*Timer/Counter2 Output Compare Flag*/

/*number of bits of timer 2*/
#define TIMER2_RESOLUTION  8

/*ENABLE/DISABLE TIMER2*/
#define ENABLE2   3  /*ENABLE TIMER2*/
#define DISABLE2  4  /*DISABLE TIMER2*/

/*Null address*/
#define NULL ((void *)0)

#endif /*MCAL_TIMER_TIMER_PRIVATE_H_*/
