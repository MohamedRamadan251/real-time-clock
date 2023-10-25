/*
 * Timer_int.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

void MTimer_voidInt (void) ;

void MTimer_voidSetDisiredTime (u8 A_u8TimerID , f32 A_f32DisiredTime , void (*A_fptr)(void) ) ;
#endif /*MCAL_TIMER_TIMER_INT_H_*/