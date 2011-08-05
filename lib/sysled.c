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

#include <sysled.h>


void sysled_init(void)
{
    uint8_t i;
    for (i=FIRST_SYSLED;i<(FIRST_SYSLED+NO_SYSLED);i++)
    {
        DDR(SYSLED_PORT) |= (1 << i);
        if (SYSLED_LOGIC & (1 << i))
            SYSLED_PORT &= ~(1 << i);
        else
            SYSLED_PORT |= (1 << i);
    }
    SysLED_stat=TRUE;
    SysLED_flashing=0;
    SysLED_time=(SYSLED_RATE >> 1);
}

void sysled_flash(uint8_t led)
{
    SysLED_flashing |= (1 << (led+FIRST_SYSLED));
}

void sysled_on(uint8_t led)
{
    uint8_t i;
    i=led+FIRST_SYSLED;
    if (SYSLED_LOGIC & (1 << i))
        SYSLED_PORT |= (1 << i);
    else
        SYSLED_PORT &= ~(1 << i);
    SysLED_flashing &= ~(1 << led);
}

void sysled_off(uint8_t led)
{
    uint8_t i;
    i=led+FIRST_SYSLED;
    if (SYSLED_LOGIC & (1 << i))
        SYSLED_PORT &= ~(1 << i);
    else
        SYSLED_PORT |= (1 << i);
    SysLED_flashing &= ~ (1 << led);
}

void sysled_allon(void)
{
    uint8_t i;
    for (i=FIRST_SYSLED;i<(FIRST_SYSLED+NO_SYSLED);i++)
    {
        if (SYSLED_LOGIC & (1 << i))
            SYSLED_PORT |= (1 << i);
        else
            SYSLED_PORT &= ~(1 << i);
        SysLED_flashing &= ~(1 << i);
    }
}

void sysled_alloff(void)
{
    uint8_t i;
    for (i=FIRST_SYSLED;i<(FIRST_SYSLED+NO_SYSLED);i++)
    {
        if (SYSLED_LOGIC & (1 << i))
            SYSLED_PORT &= ~(1 << i);
        else
            SYSLED_PORT |= (1 << i);
        SysLED_flashing &= ~(1 << i);
    }
}

void sysled_enable(uint8_t stat)
{
    SysLED_stat=stat;
}
