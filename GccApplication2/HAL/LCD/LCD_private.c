/*
 * LCD_private.c
 *
 *  Created on: May 18, 2022
 *      Author: Mohammed Ramadan
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include <util/delay.h>
#include "LCD_conf.h"
#include "LCD_private.h"

void HLCD_voidSendCmd(u8 A_u8CmdID)
{
	#if MODE == EIGHT_BIT_CONNECTION
	
	    /**set register select to low */
	    MDIO_voidClrPinVal  (LCD_RS_PORT , LCD_RS_PIN ) ;
		
		/**set read/write to low */
	    MDIO_voidClrPinVal  (LCD_RW_PORT , LCD_RW_PIN ) ;
		
		/**set enable to high */
	    MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
	    _delay_ms (1) ;
		
		/**send data to control register */
	    MDIO_voidSetPortVal (LCD_DATA_PORT , A_u8CmdID) ;
		
		/**set enable to low */
	    MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
	    _delay_ms (1) ;
	
	#elif MODE == FOUR_BIT_CONNECTION
	
	    /**set register select to low */
	    MDIO_voidClrPinVal  (LCD_RS_PORT , LCD_RS_PIN ) ;
		
		/**set read/write to low */
	    MDIO_voidClrPinVal  (LCD_RW_PORT , LCD_RW_PIN ) ;
		
		/**set enable to high */
	    MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (1) ;
		
		/**send last four bits of data to last four bit at control register */
		MDIO_voidWriteHighNibble (LCD_DATA_PORT , A_u8CmdID >> FOUR_BITS) ;
		
		/**set enable to low */
		MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
	    _delay_ms (1) ;
		
		/**set enable to high */
		MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (1) ;
		
		/**send first four bits of data to first four bit at control register */
		MDIO_voidWriteHighNibble (LCD_DATA_PORT , A_u8CmdID) ;
		
		/**set enable to low */
		MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
	    _delay_ms (1) ;
	#else 
		 #error "select write mode"
	#endif
}