#ifndef SYSTICK_H
#define SYSTICK_H

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


#include <avr/io.h>
#include <avr/interrupt.h>
#include <config.h>

/*
 * Timer0
 */
#if USE_TIMER==0
 #if ((8 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 2
	#define TCNT_VAL (256-(F_CPU / 8 / 1000 * SYSTICK))
 #elif ((64 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 3
	#define TCNT_VAL (256-(F_CPU / 64 / 1000 * SYSTICK))
 #elif ((256 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 4
	#define TCNT_VAL (256-(F_CPU / 256 / 1000 * SYSTICK))
 #elif ((1024 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 5
	#define TCNT_VAL (256-(F_CPU / 1024 / 1000 * SYSTICK))
 #endif

 #if defined(TCCR0)
  #define TIMER_PRESC TCCR0
 #elif defined(TCCR0B)
  #define TIMER_PRESC TCCR0B
 #else
  #error Timer0 not availibel on this device
 #endif
 #if defined(TIMSK)
  #define TIMER_IMSK TIMSK
 #elif defined(TIMSK0)
  #define TIMER_IMSK TIMSK0
 #endif
 #define TIMER_TOIE TOIE0
 #define TIMER_TCNT TCNT0
#else /*USE_TIMER==0*/

/* Timer2 */
 #if ((8 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 2
	#define TCNT_VAL (256-(F_CPU / 8 / 1000 * SYSTICK))
 #elif ((32 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 3
	#define TCNT_VAL (256-(F_CPU / 32 / 1000 * SYSTICK))
 #elif ((64 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 4
	#define TCNT_VAL (256-(F_CPU / 64 / 1000 * SYSTICK))
 #elif ((128 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 5
	#define TCNT_VAL (256-(F_CPU / 128 / 1000 * SYSTICK))
 #elif ((256 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 6
	#define TCNT_VAL (256-(F_CPU / 256 / 1000 * SYSTICK))
 #elif ((1024 * 256000 / F_CPU) > (SYSTICK))
	#define PRESC 7
	#define TCNT_VAL (256-(F_CPU / 1024 / 1000 * SYSTICK))
 #endif
 
 #if defined(TCCR2)
  #define TIMER_PRESC TCCR2
 #elif defined(TCCR2B)
  #define TIMER_PRESC TCCR2B
 #else
  #error Timer2 not availibel on this device
 #endif 
 #if defined(TIMSK)
  #define TIMER_IMSK TIMSK
 #elif defined(TIMSK2)
  #define TIMER_IMSK TIMSK2
 #endif
 #define TIMER_TOIE TOIE2
 #define TIMER_TCNT TCNT2
#endif /*USE_TIMER*/

/**----------------------------------
 * Prototypes
 *----------------------------------*/

/**----------------------------------
 * @brief Inits Systick
 * @param void
 * @return void
 *----------------------------------*/
void systick_init(void);


#endif
