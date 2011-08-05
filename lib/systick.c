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

#include <systick.h>


void systick_init(void)
{
// Init Timer
    TIMER_PRESC=PRESC;
    TIMER_IMSK|=(1<<TIMER_TOIE);

    #ifdef SYSTICK_SYSLED
        sysled_init();
    #endif
    #ifdef SYSTICK_SYSSWITCH
        sysswitch_init();
    #endif
    #ifdef SYSTICK_ADC
        adc_init();
    #endif
}

#if USE_TIMER==0
SIGNAL (SIG_OVERFLOW0)
#elif USE_TIMER==2
SIGNAL (SIG_OVERFLOW2)
#endif
{
    cli();
    TIMER_TCNT=TCNT_VAL;
    #if defined (SYSTICK_SYSLED) || defined(SYSTICK_SYSSWITCH)
    uint8_t i;
    #endif
    #ifdef SYSTICK_SYSLED
        if (SysLED_stat)
        {
            SysLED_time--;
            if (SysLED_time==0)
            {
                SysLED_time=(SYSLED_RATE >> 1);
                for (i=FIRST_SYSLED;i<(FIRST_SYSLED+NO_SYSLED);i++)
                {
                    if (SysLED_flashing & (1 << i))
                    {
                        if (SYSLED_PORT & (1 << i))
                            SYSLED_PORT &= ~(1 << i);
                        else
                            SYSLED_PORT |= (1 << i);
                    }
                }
            }
        }
    #endif
    #ifdef SYSTICK_SYSSWITCH
        Debounce_Count--;
        if (Debounce_Count == 0)
        {
            Debounce_Count = SYSSWITCH_DEBOUNCE;
            for (i = FIRST_SYSSWITCH ; i < FIRST_SYSSWITCH+NO_SYSSWITCH ; i++)
            {
                if (((PIN(SYSSWITCH_PORT) & (1 << i)) == (SYSSWITCH_LOGIC & (1 << i))) && (SysSwitchTemp & (1 << i)))
                {
                    SysSwitchPort |= (1 << i);
                }
                else if ((PIN(SYSSWITCH_PORT) & (1 << i)) == (SYSSWITCH_LOGIC & (1 << i)))
                    SysSwitchTemp |= (1 << i);
                else
                {
                    SysSwitchPort &= ~(1 << i);
                    SysSwitchTemp &= ~(1 << i);
                }
            }
        }
    #endif
    #ifdef SYSTICK_ADC
        if (ADC_Ready == TRUE)
        {
            ADC_Ready = FALSE;
            act_chan = FIRST_ADC_CHAN;
            ADMUX &= 0xE0|FIRST_ADC_CHAN;
            ADCSRA |= (1 << ADSC);
        }
    #endif
    sei();
}
