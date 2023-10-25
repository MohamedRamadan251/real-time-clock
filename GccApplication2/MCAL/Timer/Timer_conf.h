/*
 * Timer_conf.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_CONF_H_
#define MCAL_TIMER_TIMER_CONF_H_

        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/
/**ENABLE/DISABLE TIMER0
   **Options
       *ENABLE0
       *DISABLE0
 */
#define TIMER0  ENABLE0

/**select prescaller of clk timer0
   **Options
       *CLK_PS_1         
       *CLK_PS_8         
       *CLK_PS_64        
       *CLK_PS_256       
       *CLK_PS_1024      
       *EXIT_FALLING_EDGE
       *EXIT_RISING_EDGE 
 */
#define TIMER0_PRESCALER  CLK_PS_8

/**select mode of timer0
   **Options
       *NORMAL_MODE         
       *PWM_PHASE_CORRECT_MODE         
       *COMPARE_MATCH_MODE        
       *FAST_PWM_MODE       
 */
#define TIMER0_MODE NORMAL_MODE
        /****************************************************************/
        /*                         TIMER1                               */
        /****************************************************************/
/**ENABLE/DISABLE TIMER1
   **Options
       *ENABLE1
       *DISABLE1
 */
#define TIMER1  DISABLE1

        /****************************************************************/
        /*                         TIMER2                               */
        /****************************************************************/
/**ENABLE/DISABLE TIMER2
   **Options
       *ENABLE2
       *DISABLE2
 */
#define TIMER2  DISABLE2

#endif /*MCAL_TIMER_TIMER_CONF_H_*/