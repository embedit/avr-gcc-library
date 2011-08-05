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
#include <sysadc.h>


void adc_init(void)
{
    ADMUX=(ADC_REF<<6);
    ADC_Ready=FALSE;
    #ifdef DIDR0
        uint8_t j;
        for (j=FIRST_ADC_CHAN; j<FIRST_ADC_CHAN+NO_ADC_CHANS; j++)
            DIDR0|=(1<<j);
    #endif
}

unsigned int adc_get(uint8_t chan)
{
    while((ADC_Ready==TRUE));
    return ADC_CHANS[chan-FIRST_ADC_CHAN];
}

void adc_start(void)
{
    ADCSRA=(1<<ADEN)|(1<<ADIE)|ADC_PRESC;
    ADC_Ready=FALSE;
    act_chan=FIRST_ADC_CHAN;
    ADMUX=((ADC_REF<<6)+FIRST_ADC_CHAN);
    ADCSRA|=(1<<ADSC);
}

void adc_stop(void)
{
    ADCSRA=0;
    ADC_Ready=FALSE;
}

uint8_t adc_stat(void)
{
    return ADC_Ready;
}

SIGNAL(SIG_ADC)
{
    ADC_CHANS[act_chan-FIRST_ADC_CHAN]=ADC;

    act_chan++;
    if (act_chan<FIRST_ADC_CHAN+NO_ADC_CHANS)
    {
        ADMUX=((ADC_REF<<6)+act_chan);
        ADCSRA|=(1<<ADSC);
    }
    else
    {
        ADC_Ready=TRUE;
    }
}

