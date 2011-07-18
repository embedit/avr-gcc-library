#ifndef CONFIG_H
#define CONFIG_H
/*------------------------------------------------------------------------------
 * Copyright 1994-2008 The FreeBSD Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *	this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *	this list of conditions and the following disclaimer in the documentation
 *	and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *----------------------------------------------------------------------------*/

#include <avr/io.h>
#include <utils.h>

/*------------------------------------------------------------------------------
 * Defines for USART0
 * define Receive Buffer Size. Size can be 2, 4, 8, 16, 32, 64, 128 or 256 Byte
 * define Transmit Buffer Size. Size can be 2, 4, 8, 16, 32, 64, 128 or 256 Byte
 *----------------------------------------------------------------------------*/
#define BAUD0 9600
#define USART0_RX_BUFFER_SIZE 32
#define USART0_TX_BUFFER_SIZE 32

#define RS485_0_PORT	PORTD
#define RS485_0_DDR		DDRD
#define RS485_0_BIT		PD2


/*------------------------------------------------------------------------------
 * Defines for LCD
 *----------------------------------------------------------------------------*/
#define LCD_ROWS        4				// Number of Rows
#define LCD_COLS        20				// Number of Columns
#define LCD_DATA_PORT   PORTB			// Port Register of the LCD Data Port
#define LCD_D4          0				// Port Bit connected to D4 of the LCD
#define LCD_CTRL_PORT   PORTD			// Port Register for the LCD control signals
#define LCD_RS          6				// Port Bit of the RS Signal
#define LCD_RW          5				// Port Bit of the RW Signal
#define LCD_E           4				// Port Bit of the Enable Signal
#define LCD_BL          3				// Port Bit to control the Backlight


/*------------------------------------------------------------------------------
 * Defines for Utils
 *----------------------------------------------------------------------------*/
// Don't remove
#include <sysswitch.h>				// SysSwitch must be included here.

/*-----------------------------------
 * LINE_END defines the Line Ending for writeln() and writeln_p()
 * 0=UNIX='\n'
 * 1=MAC='\r'
 * 2=WIN='\r\n'
 *----------------------------------*/
#define LINE_END 2

/*-----------------------------------
 * Define your IO here
 * Examples for LED at PORTD.0 and switch at PIND.1
 * #define LED1	   BIT(PORTD, 0)
 * #define SWITCH1	BIT(PIND, 1)
 *----------------------------------*/
#define LED1		BIT(PORTB,0)
#define SWITCH1		BIT(PINB,1)
//#define Switch	BIT(SysSwitchPort,1)	// define a Switch on SysSwitchPort

/*------------------------------------------------------------------------------
 * Generic Defines and Includes
 * Don't touch
 *----------------------------------------------------------------------------*/

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#if defined (SYSTICK)
  #include <systick.h>
#endif

#if defined (SYSTICK_SYSLED)
  #include <sysled.h>
#endif

#if defined (SYSTICK_ADC)
  #include <sysadc.h>
#endif

#if defined (BAUD0)
  #include <usart.h>
#endif

#if defined (BAUD1)
  #include <usart1.h>
#endif

#if defined (BAUD2)
  #include <usart2.h>
#endif

#if defined (BAUD3)
  #include <usart3.h>
#endif

#endif  /*CONFIG_H*/
