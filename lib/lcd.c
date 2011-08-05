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
#include "lcd.h"

#if LCD_ROWS==1
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_1LINE
#else
#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES
#endif

static void lcd_pulse_e(void)
{
    LCD_CTRL_PORT |=  (1 << LCD_E);
    _delay_us(5);
    LCD_CTRL_PORT &= ~(1 << LCD_E);
}

static void lcd_write(uint8_t data,uint8_t rs)
{
    unsigned char dataBits ;
    cli();

    if (rs) {
        LCD_CTRL_PORT |=  (1 << LCD_RS);
    } else {
        LCD_CTRL_PORT &= ~(1 << LCD_RS);
    }
    LCD_CTRL_PORT &= ~(1 << LCD_RW);

#if LCD_D4==4
        DDR(LCD_DATA_PORT) |= 0xF0;
        dataBits = LCD_DATA_PORT & 0x0F;
        LCD_DATA_PORT = (dataBits|(data&0xF0));
        lcd_pulse_e();
        LCD_DATA_PORT = (dataBits|((data<<4)&0xF0));
        lcd_pulse_e();
        LCD_DATA_PORT = (dataBits | 0xF0);
#else
        DDR(LCD_DATA_PORT) |= 0x0F;
        dataBits = LCD_DATA_PORT & 0xF0;
        LCD_DATA_PORT = dataBits |((data>>4)&0x0F);
        lcd_pulse_e();
        LCD_DATA_PORT = dataBits | (data&0x0F);
        lcd_pulse_e();
        LCD_DATA_PORT = dataBits | 0x0F;
#endif
        sei();
}

static uint8_t lcd_read(uint8_t rs)
{
    uint8_t data;

    cli();
    if (rs) {
        LCD_CTRL_PORT |=  (1 << LCD_RS);
    } else {
        LCD_CTRL_PORT &= ~(1 << LCD_RS);
    }
    LCD_CTRL_PORT |=  (1 << LCD_RW);

#if LCD_D4==4
        DDR(LCD_DATA_PORT) &= 0x0F;
        LCD_CTRL_PORT |=  (1 << LCD_E);
        _delay_us(5);
        data = PIN(LCD_DATA_PORT);
        LCD_CTRL_PORT &= ~(1 << LCD_E);
        _delay_us(5);
        LCD_CTRL_PORT |=  (1 << LCD_E);
        _delay_us(5);
        data |= (PIN(LCD_DATA_PORT)&0x0F) >> 4;
        LCD_CTRL_PORT &= ~(1 << LCD_E);
#else
        DDR(LCD_DATA_PORT) &= 0xF0;
        LCD_CTRL_PORT |=  (1 << LCD_E);
        _delay_us(5);
        data = PIN(LCD_DATA_PORT) << 4;
        LCD_CTRL_PORT &= ~(1 << LCD_E);
        _delay_us(5);
        LCD_CTRL_PORT |=  (1 << LCD_E);
        _delay_us(5);
        data |= PIN(LCD_DATA_PORT)&0x0F;
        LCD_CTRL_PORT &= ~(1 << LCD_E);
#endif
    sei();
    return data;
}

static uint8_t lcd_waitbusy(void)
{
    register uint8_t c;
    while ( (c=lcd_read(0)) & (1<<LCD_BUSY)) {}
    _delay_us(4);
    return (lcd_read(0));

}/* lcd_waitbusy */

void lcd_cmd(uint8_t cmd)
{
    lcd_waitbusy();
    lcd_write(cmd,0);
}

void lcd_data(uint8_t data)
{
    lcd_waitbusy();
    lcd_write(data,1);
}

void lcd_putc(char c)
{
    lcd_waitbusy();
    lcd_write(c, 1);

}/* lcd_putc */

void lcd_init(uint8_t dispAttr)
{

    DDR(LCD_CTRL_PORT) |= (1 << LCD_RS);
    DDR(LCD_CTRL_PORT) |= (1 << LCD_RW);
    DDR(LCD_CTRL_PORT) |= (1 << LCD_E);
#if LCD_D4==0
    DDR(LCD_DATA_PORT) |= 0x0F;
#else
    DDR(LCD_DATA_PORT) |= 0xF0;
#endif
    _delay_ms(16);//16
    LCD_DATA_PORT |= (LCD_ON << LCD_D4);
    lcd_pulse_e();
    _delay_ms(5);//5
    lcd_pulse_e();
    _delay_ms(1);
    lcd_pulse_e();
    _delay_ms(1);
    LCD_DATA_PORT &= ~(1 << LCD_D4);
    lcd_pulse_e();
    _delay_ms(1);

    lcd_cmd(LCD_FUNCTION_DEFAULT);
    lcd_cmd(LCD_DISP_OFF);
    lcd_cmd(LCD_CLR);
    lcd_cmd(LCD_MODE_DEFAULT);
    lcd_cmd(dispAttr);
}/* lcd_init */
