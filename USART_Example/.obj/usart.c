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


#include "usart.h"

/* Static Variables */
static char USART0_RxBuf[USART0_RX_BUFFER_SIZE];
static volatile char USART0_RxHead;
static volatile char USART0_RxTail;
static char USART0_TxBuf[USART0_TX_BUFFER_SIZE];
static volatile char USART0_TxHead;
static volatile char USART0_TxTail;

/* Initialize USART */
void usart0_init( void )
{
    UBRR0L = UBRRL_VALUE;
    UBRR0H = UBRRH_VALUE;
    UCSR0B = ( ( 1 << RXCIE0 ) | ( 1 << RXEN0 ) | ( 1 << TXEN0 ) );
    #ifdef URSEL
        UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
    #else
        UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
    #endif
#if USE_2X
    UCSR0A |= (1 << U2X0);
#endif /*USE_2X*/
    USART0_RxTail = 0;
    USART0_RxHead = 0;
    USART0_TxTail = 0;
    USART0_TxHead = 0;
}


ISR(UART0_RECV_IRQ)
{
    char data;
    unsigned char tmp;
    data = UDR0;
    tmp = ( USART0_RxHead + 1 ) & USART0_RX_BUFFER_MASK;
    USART0_RxHead = tmp;
    USART0_RxBuf[tmp] = data;
}

ISR(UART0_DATA_IRQ)
{
    unsigned char tmp;

    if ( USART0_TxHead != USART0_TxTail )
    {
        tmp = ( USART0_TxTail + 1 ) & USART0_TX_BUFFER_MASK;
        USART0_TxTail = tmp;
        UDR0 = USART0_TxBuf[tmp];
    }
    else
    {
        UCSR0B &= ~(1<<UDRIE0);
    }
}

char usart0_getc( void )
{
    unsigned char tmp;

    while ( USART0_RxHead == USART0_RxTail );
    tmp = ( USART0_RxTail + 1 ) & USART0_RX_BUFFER_MASK;
    USART0_RxTail = tmp;
    return USART0_RxBuf[tmp];
}

void usart0_putc( char data )
{
    unsigned char tmp;
    tmp = ( USART0_TxHead + 1 ) & USART0_TX_BUFFER_MASK;
    while ( tmp == USART0_TxTail );
    USART0_TxBuf[tmp] = data;
    USART0_TxHead = tmp;
    UCSR0B |= (1<<UDRIE0);
}

char usart0_data_received( void )
{
    return ( USART0_RxHead != USART0_RxTail );
}
