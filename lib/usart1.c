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


#include "usart1.h"

/* Static Variables */
static char USART1_RxBuf[USART1_RX_BUFFER_SIZE];
static volatile char USART1_RxHead;
static volatile char USART1_RxTail;
static char USART1_TxBuf[USART1_TX_BUFFER_SIZE];
static volatile char USART1_TxHead;
static volatile char USART1_TxTail;

/* Initialize USART */
void usart1_init( void )
{
    #undef BAUD  // avoid compiler warning
    #define BAUD BAUD1
    #include <util/setbaud.h>
    UBRR1L = UBRRL_VALUE;
    UBRR1H = UBRRH_VALUE;
    UCSR1B = ( ( 1 << RXCIE1 ) | ( 1 << RXEN1 ) | ( 1 << TXEN1 ) );
    UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);
#if USE1_2X
    UCSR1A |= (1 << U2X1);
#endif /*USE_2X*/
    USART1_RxTail = 0;
    USART1_RxHead = 0;
    USART1_TxTail = 0;
    USART1_TxHead = 0;

/* Init direction Pin for RS485 Driver, if RS485 is used */
#ifdef RS485_1_PORT
    UCSR1B |= (1 << TXCIE1);
    RS485_1_PORT &= ~(1<<RS485_1_BIT);
    RS485_1_DDR |= (1<<RS485_1_BIT);
#endif /*RS485_1_PORT*/
}

char usart1_getc( void )
{
    unsigned char tmp;

    while ( USART1_RxHead == USART1_RxTail );
    tmp = ( USART1_RxTail + 1 ) & USART1_RX_BUFFER_MASK;
    USART1_RxTail = tmp;
    return USART1_RxBuf[tmp];
}

void usart1_putc( char data )
{
    unsigned char tmp;
    tmp = ( USART1_TxHead + 1 ) & USART1_TX_BUFFER_MASK;
    while ( tmp == USART1_TxTail );
    USART1_TxBuf[tmp] = data;
    USART1_TxHead = tmp;
    UCSR1B |= (1<<UDRIE1);
}

char usart1_data_received( void )
{
    return ( USART1_RxHead != USART1_RxTail );
}

ISR(USART1_RX_vect)
{
    char data;
    unsigned char tmp;
    data = UDR1;
    tmp = ( USART1_RxHead + 1 ) & USART1_RX_BUFFER_MASK;
    USART1_RxHead = tmp;
    USART1_RxBuf[tmp] = data;
}

ISR(USART1_UDRE_vect)
{
    unsigned char tmp;

    if ( USART1_TxHead != USART1_TxTail )
    {
        #ifdef RS485_1_PORT
            RS485_1_PORT |= (1 << RS485_1_BIT);
        #endif /*RS485_1_PORT*/
        tmp = ( USART1_TxTail + 1 ) & USART1_TX_BUFFER_MASK;
        USART1_TxTail = tmp;
        UDR1 = USART1_TxBuf[tmp];
    }
    else
    {
        UCSR1B &= ~(1<<UDRIE1);
    }
}

#ifdef RS485_1_PORT
ISR(UART1_TXC_IRQ)
{
    RS485_1_PORT &= ~(1<<RS485_1_BIT);
}
#endif /*RS485_1_PORT*/
