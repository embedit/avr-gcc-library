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
#ifndef LCD_H
#define LCD_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <config.h>

/*@{*/


#ifndef LCD_ROWS
    #error "The Parameter LCD_ROWS is not defined in the Project.\
    Please add the Parameter to the config.h"
#endif /*LCD_ROWS*/

#ifndef LCD_COLS
    #error "The Parameter LCD_COLS is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif /*LCD_DISP_LENGTH*/

#ifndef LCD_DATA_PORT
    #error "The Parameter LCD_DATA_PORT is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#ifndef LCD_D4
    #error "The Parameter LCD_D4 is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#ifndef LCD_CTRL_PORT
    #error "The Parameter LCD_CTRL_PORT is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#ifndef LCD_RS
    #error "The Parameter LCD_RS is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#ifndef LCD_RW
    #error "The Parameter LCD_RW is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#ifndef LCD_E
    #error "The Parameter LCD_E is not defined in the Project.\
    Please add the Parameter to the config.h."
#endif

#define LCD_BUSY              7         // LCD busy
#define LCD_CGRAM             6         // set CG RAM address
#define LCD_CLR               1         // clear display
#define LCD_DDRAM             7         // set DDRAM address
#define LCD_HOME              1         // return to home position
#define LCD_ENTRY_MODE        2         // set entry mode
#define LCD_ENTRY_INC         1         // 1=increment, 0=decrement
#define LCD_ENTRY_SHIFT       0         // 1=display shift on
#define LCD_ON                3         // lcd on
#define LCD_ON_DISPLAY        2         // display on
#define LCD_ON_CURSOR         1         // cursor on
#define LCD_ON_BLINK          0         // blinking cursor
#define LCD_MOVE              4         // move cursor/display
#define LCD_MOVE_DISP         3         // move display
#define LCD_MOVE_RIGHT        2         // move right
#define LCD_FUNCTION          5         // function set
#define LCD_FUNCTION_2LINES   3         // two lines (0->one line)

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC            0x04   /* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT      0x05   /* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC_           0x06   /* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT      0x07   /* display shift on,  inc cursor move dir */

/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF             0x08   /* display off                            */
#define LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */

/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */

/* function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */

#ifndef LCD_MODE_DEFAULT
    #define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )
#endif


extern void lcd_init(uint8_t dispAttr);
extern void lcd_clr(void);
extern void lcd_home(void);
extern void lcd_gotoxy(uint8_t x, uint8_t y);
extern void lcd_putc(char c);
extern void lcd_cmd(uint8_t cmd);
extern void lcd_data(uint8_t data);

/*@}*/
#endif /* LCD_H */
