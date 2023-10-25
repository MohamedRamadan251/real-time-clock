/*
 * GccApplication1.c
 *
 * Created: 7/29/2022 8:10:59 PM
 *  Author: maka
 */ 


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "HAL/KeyPad/KP_int.h"
#include "HAL/LCD/LCD_int.h"
#include "MCAL/Timer/Timer_int.h"
#include "MCAL/DIO/DIO_int.h"
#define F_CPU 8000000UL
#include "util/delay.h"
static u8 R_u8SsdData [] = {
	0x3f,    /**0*/
	0x06,    /**1*/
	0x5b,    /**2*/
	0x4f,    /**3*/
	0x66,    /**4*/
	0x6d,    /**5*/
	0x7d,    /**6*/
	0x07,    /**7*/
	0x7f,    /**8*/
	0x6f     /**9*/
} ;
	volatile u8 L_u8Seconds = 0 ;
	u8 L_u8Minits  = 0 ;
	u8 L_u8Hours   = 0 ;
void Timer_action ( void )
{
	L_u8Seconds ++ ;
}
int main(void)
{
	u8 L_u8FirstDigit = 0 ;
	u8 L_u8SecondDigit = 0 ;
	MTimer_voidInt() ;
	HLCD_voidInit() ;
	HKP_voidKpInt() ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN0 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN1 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN2 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN3 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN4 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN5 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTA , DIO_PIN6 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN0 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN1 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN2 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN3 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN4 , DIO_HIGH) ;
	MDIO_voidSetPinDir(DIO_PORTC , DIO_PIN5 , DIO_HIGH) ;
    while(1)
    {
		u8 L_u8ValueSelect = HKP_u8GetPressedKey() ;
		MTimer_voidSetDisiredTime(1 , 1 , Timer_action) ;
		if (L_u8ValueSelect == '1') 
		{
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN0) ;
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN1) ;
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN2) ;
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN3) ;
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN4) ;
			MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN5) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN0) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN1) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN2) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN3) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN4) ;
			MDIO_voidClrPinVal(DIO_PORTA , DIO_PIN5) ;
			MDIO_voidSetPinVal(DIO_PORTA , DIO_PIN6) ;
			HLCD_voidClrScreen() ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidDispStr("--:--:--") ;				  
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidDispStr("Hours = --") ;
			HLCD_voidMovCursor(2 , 9) ;
			do 
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if (L_u8Value < '3' && L_u8Value >= '0')
				{
					L_u8FirstDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(2 , 10) ;
			do
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if ((L_u8FirstDigit < 2 && L_u8Value <= '9' && L_u8Value >= '0')||(L_u8FirstDigit == 2 && L_u8Value <= '3' && L_u8Value >= '0'))
				{
					L_u8SecondDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			HLCD_voidMovCursor(1,2) ;
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			L_u8Hours = (L_u8FirstDigit * 10) + L_u8SecondDigit ;
			_delay_ms(500) ;
			HLCD_voidClrScreen() ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidDispIntNum(L_u8Hours/10) ;
			HLCD_voidDispIntNum(L_u8Hours%10) ;
			HLCD_voidDispStr(":--:--") ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidDispStr("minute = --") ;
			HLCD_voidMovCursor(2 , 10) ;
			do
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if (L_u8Value < '6' && L_u8Value >= '0')
				{
					L_u8FirstDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(1,4) ;
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(2 , 11) ;
			do
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if (L_u8Value <= '9' && L_u8Value >= '0')
				{
					L_u8SecondDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			HLCD_voidMovCursor(1,5) ;
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			L_u8Minits = (L_u8FirstDigit * 10) + L_u8SecondDigit ;
			_delay_ms(500) ;
			HLCD_voidClrScreen() ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidMovCursor(1,1) ;
			HLCD_voidDispIntNum(L_u8Hours/10) ;
			HLCD_voidDispIntNum(L_u8Hours%10) ;
			HLCD_voidDispStr(":") ;
			HLCD_voidDispIntNum(L_u8Minits/10) ;
			HLCD_voidDispIntNum(L_u8Minits%10) ;
			HLCD_voidDispStr(":--") ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidMovCursor(2 , 1) ;
			HLCD_voidDispStr("seconds = --") ;
			HLCD_voidMovCursor(2 , 11) ;
			do
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if (L_u8Value < '6' && L_u8Value >= '0')
				{
					L_u8FirstDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(1,7) ;
			HLCD_voidDispIntNum(L_u8FirstDigit) ;
			HLCD_voidMovCursor(2,12) ;
			do
			{
				u8 L_u8Value = HKP_u8GetPressedKey() ;
				if (L_u8Value <= '9' && L_u8Value >= '0')
				{
					L_u8SecondDigit = L_u8Value - '0' ;
					break ;
				}
			} while (1);
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			HLCD_voidMovCursor(1,8) ;
			HLCD_voidDispIntNum(L_u8SecondDigit) ;
			L_u8Seconds = (L_u8FirstDigit * 10) + L_u8SecondDigit ;
			_delay_ms(500) ;
		}
		if (L_u8Seconds == 60)
		{
			L_u8Minits ++ ;
			L_u8Seconds = 0 ;
		}
		if (L_u8Minits == 60)
		{
			L_u8Hours ++ ;
			L_u8Minits = 0 ;
		}
		if (L_u8Hours == 24)
		{
			L_u8Hours = 0 ;
			L_u8Minits = 0 ;
			L_u8Seconds = 0 ;
		}
		HLCD_voidClrScreen() ;
		HLCD_voidMovCursor(1,1) ;
		HLCD_voidMovCursor(1,1) ;
		HLCD_voidMovCursor(1,1) ;
		HLCD_voidDispStr("Set 1 to set T") ;
		HLCD_voidMovCursor(2,1) ;
		HLCD_voidMovCursor(2,1) ;
		HLCD_voidMovCursor(2,1) ;
		HLCD_voidDispIntNum(L_u8Hours) ;
		HLCD_voidDispStr(":") ;
		HLCD_voidDispIntNum(L_u8Minits) ;
		HLCD_voidDispStr(":") ;
		HLCD_voidDispIntNum(L_u8Seconds) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN5) ;
       	MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Seconds % 10]) ;
		_delay_ms(4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN5) ;
		MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Seconds / 10]) ; 
		_delay_ms(4) ; 
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN5) ;
		MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Minits % 10]) ; 
		_delay_ms(4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN5) ;
		MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Minits / 10]) ; 
		_delay_ms(4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN5) ;
		MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Hours % 10]) ; 
		_delay_ms(4) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN0) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN1) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN2) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN3) ;
		MDIO_voidSetPinVal(DIO_PORTC , DIO_PIN4) ;
		MDIO_voidClrPinVal(DIO_PORTC , DIO_PIN5) ;
		MDIO_voidSetPortVal(DIO_PORTA , R_u8SsdData [L_u8Hours / 10]) ; 
		_delay_ms(4) ;
    }
}
