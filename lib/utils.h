#ifndef UTILS_H
#define UTILS_H
/*------------------------------------------------------------------------------
 * Copyright 1994-2008 The FreeBSD Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
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

#include <avr/pgmspace.h>
#include <config.h>

/**----------------------------------
 * @brief creat a bitfield and defines the BIT() makro
 *----------------------------------*/

struct bitfield {
  unsigned char b0:1;
  unsigned char b1:1;
  unsigned char b2:1;
  unsigned char b3:1;
  unsigned char b4:1;
  unsigned char b5:1;
  unsigned char b6:1;
  unsigned char b7:1;
} __attribute__((__packed__));

#define BIT(r,n) (((volatile struct bitfield *)&r)->b##n)

/**----------------------------------
 * @brief use DDR and PIN Registers without define
 * 
 *----------------------------------*/
#define DDR(x) (*(&x - 1))
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__)
    #define PIN(x) ( &PORTF==&(x) ? _SFR_IO8(0x00) : (*(&x - 2)) )
#else
    #define PIN(x) (*(&x - 2))
#endif

#if defined (__AVR_ATmega32__)
	#define OUT_0 BIT(PORTB,0)
	#define OUT_1 BIT(PORTB,1)
	#define OUT_2 BIT(PORTB,2)
	#define OUT_3 BIT(PORTB,3)
	#define OUT_4 BIT(PORTB,4)
	#define OUT_5 BIT(PORTB,5)
	#define OUT_6 BIT(PORTB,6)
	#define OUT_7 BIT(PORTB,7)
	#define OUT_8 BIT(PORTD,0)
	#define OUT_9 BIT(PORTD,1)
	#define OUT_10 BIT(PORTD,2)
	#define OUT_11 BIT(PORTD,3)
	#define OUT_12 BIT(PORTD,4)
	#define OUT_13 BIT(PORTD,5)
	#define OUT_14 BIT(PORTD,6)
	#define OUT_15 BIT(PORTD,7)
	#define OUT_16 BIT(PORTC,0)
	#define OUT_17 BIT(PORTC,1)
	#define OUT_18 BIT(PORTC,2)
	#define OUT_19 BIT(PORTC,3)
	#define OUT_20 BIT(PORTC,4)
	#define OUT_21 BIT(PORTC,5)
	#define OUT_22 BIT(PORTC,6)
	#define OUT_23 BIT(PORTC,7)
	#define OUT_24 BIT(PORTA,7)
	#define OUT_25 BIT(PORTA,6)
	#define OUT_26 BIT(PORTA,5)
	#define OUT_27 BIT(PORTA,4)
	#define OUT_28 BIT(PORTA,3)
	#define OUT_29 BIT(PORTA,2)
	#define OUT_30 BIT(PORTA,1)
	#define OUT_31 BIT(PORTA,0)
	#define IN_0 BIT(PINB,0)
	#define IN_1 BIT(PINB,1)
	#define IN_2 BIT(PINB,2)
	#define IN_3 BIT(PINB,3)
	#define IN_4 BIT(PINB,4)
	#define IN_5 BIT(PINB,5)
	#define IN_6 BIT(PINB,6)
	#define IN_7 BIT(PINB,7)
	#define IN_8 BIT(PIND,0)
	#define IN_9 BIT(PIND,1)
	#define IN_10 BIT(PIND,2)
	#define IN_11 BIT(PIND,3)
	#define IN_12 BIT(PIND,4)
	#define IN_13 BIT(PIND,5)
	#define IN_14 BIT(PIND,6)
	#define IN_15 BIT(PIND,7)
	#define IN_16 BIT(PINC,0)
	#define IN_17 BIT(PINC,1)
	#define IN_18 BIT(PINC,2)
	#define IN_19 BIT(PINC,3)
	#define IN_20 BIT(PINC,4)
	#define IN_21 BIT(PINC,5)
	#define IN_22 BIT(PINC,6)
	#define IN_23 BIT(PINC,7)
	#define IN_24 BIT(PINA,7)
	#define IN_25 BIT(PINA,6)
	#define IN_26 BIT(PINA,5)
	#define IN_27 BIT(PINA,4)
	#define IN_28 BIT(PINA,3)
	#define IN_29 BIT(PINA,2)
	#define IN_30 BIT(PINA,1)
	#define IN_31 BIT(PINA,0)
	#define DIR_0 BIT(DDRB,0)
	#define DIR_1 BIT(DDRB,1)
	#define DIR_2 BIT(DDRB,2)
	#define DIR_3 BIT(DDRB,3)
	#define DIR_4 BIT(DDRB,4)
	#define DIR_5 BIT(DDRB,5)
	#define DIR_6 BIT(DDRB,6)
	#define DIR_7 BIT(DDRB,7)
	#define DIR_8 BIT(DDRD,0)
	#define DIR_9 BIT(DDRD,1)
	#define DIR_10 BIT(DDRD,2)
	#define DIR_11 BIT(DDRD,3)
	#define DIR_12 BIT(DDRD,4)
	#define DIR_13 BIT(DDRD,5)
	#define DIR_14 BIT(DDRD,6)
	#define DIR_15 BIT(DDRD,7)
	#define DIR_16 BIT(DDRC,0)
	#define DIR_17 BIT(DDRC,1)
	#define DIR_18 BIT(DDRC,2)
	#define DIR_19 BIT(DDRC,3)
	#define DIR_20 BIT(DDRC,4)
	#define DIR_21 BIT(DDRC,5)
	#define DIR_22 BIT(DDRC,6)
	#define DIR_23 BIT(DDRC,7)
	#define DIR_24 BIT(DDRA,7)
	#define DIR_25 BIT(DDRA,6)
	#define DIR_26 BIT(DDRA,5)
	#define DIR_27 BIT(DDRA,4)
	#define DIR_28 BIT(DDRA,3)
	#define DIR_29 BIT(DDRA,2)
	#define DIR_30 BIT(DDRA,1)
	#define DIR_31 BIT(DDRA,0)
#endif

#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT 0

/**----------------------------------
 * Prototypes
 *----------------------------------*/

/**----------------------------------
 * @brief Send a string to function *f
 * @param *f function pointer
 * @param *s string
 * @return void
 *----------------------------------*/
void write(void (*f)(char), const char *s );

/**----------------------------------
 * @brief Send a string to function *f with Line End
 * @param *f function pointer
 * @param *s string
 * @return void
 *----------------------------------*/
void writeln(void (*f)(char), const char *s );

/**----------------------------------
 * @brief Send a string from Flash to function *f
 * @param *f function pointer
 * @param *s const string
 * @return void
 *----------------------------------*/
void write_p(void (*f)(char), const char *progmem_s );

/**----------------------------------
 * @brief Send a string from Flash to function *f with Line End
 * @param *f function pointer
 * @param *s const string
 * @return void
 *----------------------------------*/
void writeln_p(void (*f)(char), const char *progmem_s );

#endif
