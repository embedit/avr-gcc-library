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
