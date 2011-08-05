#ifndef SYSADC_H
#define SYSADC_H
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
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <config.h>

#define ADC_PRESC_2         0x01    //CPU clk/2
#define ADC_PRESC_4         0x02    //CPU clk/4
#define ADC_PRESC_8         0x03    //CPU clk/8
#define ADC_PRESC_16        0x04    //CPU clk/16
#define ADC_PRESC_32        0x05    //CPU clk/32
#define ADC_PRESC_64        0x06    //CPU clk/64
#define ADC_PRESC_128       0x07    //CPU clk/128

#define ADC_REF_AREF        0x00    //AREF pin
#define ADC_REF_AVCC        0x01    //AVCC pin
#define ADC_REF_INT         0x03    //Internal Reference

#define ADC0                0x00
#define ADC1                0x01
#define ADC2                0x02
#define ADC3                0x03
#define ADC4                0x04
#define ADC5                0x05
#define ADC6                0x06
#define ADC7                0x07
#if defined(__AVR_ATtiny26__)
  #define ADC8				0x08
  #define ADC9				0x09
  #define ADC10				0x0A
#elif defined(__AVR__ATmega2560__)
  #define ADC8              0x00
  #define ADC9              0x01
  #define ADC10             0x02
  #define ADC11             0x03
  #define ADC12             0x04
  #define ADC13             0x05
  #define ADC14             0x06
  #define ADC15             0x07
#endif

#define ADC_GAP             0x1E
#define ADC_AGND            0x1F

unsigned int ADC_CHANS[NO_ADC_CHANS];    //Array for results
uint8_t act_chan;               //actual ADC Channel
uint8_t ADC_Ready;

/*------------------------------------------------------------------------------
 * Fixes for ADC
 *----------------------------------------------------------------------------*/
#ifdef ADCSR
 #ifndef ADCSRA
  #define ADCSRA ADCSR
 #endif
#endif

/**----------------------------------
 * Prototypes
 *----------------------------------*/

/**----------------------------------
 * @brief Inits ADC
 * @param void
 * @return void
 *----------------------------------*/
void adc_init(void);

/**----------------------------------
 * @brief Get ADC Vylue
 * @param ADC Channel Number
 * @return ADC Value
 *----------------------------------*/
unsigned int adc_get(uint8_t chan);

/**----------------------------------
 * @brief Start Conversion
 * @param void
 * @return void
 *----------------------------------*/
void adc_start(void);

/**----------------------------------
 * @brief Get ADC Status
 * @param void
 * @return Status of ADC
 *----------------------------------*/
uint8_t adc_stat(void);

/**----------------------------------
 * @brief Stop Conversion
 * @param void
 * @return void
 *----------------------------------*/
void adc_stop(void);

#endif
