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


#include "usart2.h"

/* Static Variables */
static char USART2_RxBuf[USART2_RX_BUFFER_SIZE];
static volatile char USART2_RxHead;
static volatile char USART2_RxTail;
static char USART2_TxBuf[USART2_TX_BUFFER_SIZE];
static volatile char USART2_TxHead;
static volatile char USART2_TxTail;

/* Initialize USART */
void usart2_init( void )
{
    #undef BAUD  // avoid compiler warning
    #define BAUD BAUD2
    #include <util/setbaud.h>
    UBRR2L = UBRRL_VALUE;
    UBRR2H = UBRRH_VALUE;
    UCSR2B = ( ( 1 << RXCIE2 ) | ( 1 << RXEN2 ) | ( 1 << TXEN2 ) );
    UCSR2C = (1<<UCSZ21)|(1<<UCSZ20);
#if USE2_2X
    UCSR2A |= (1 << U2X2);
#endif /*USE_2X*/
    USART2_RxTail = 0;
    USART2_RxHead = 0;
    USART2_TxTail = 0;
    USART2_TxHead = 0;

/* Init direction Pin for RS485 Driver, if RS485 is used */
#ifdef RS485_2_PORT
    UCSR2B |= (1 << TXCIE2);
    RS485_2_PORT &= ~(1<<RS485_2_BIT);
    RS485_2_DDR |= (1<<RS485_2_BIT);
#endif /*RS485_1_PORT*/
}

char usart2_getc( void )
{
    unsigned char tmp;

    while ( USART2_RxHead == USART2_RxTail );
    tmp = ( USART2_RxTail + 1 ) & USART2_RX_BUFFER_MASK;
    USART2_RxTail = tmp;
    return USART2_RxBuf[tmp];
}

void usart2_putc( char data )
{
    unsigned char tmp;
    tmp = ( USART2_TxHead + 1 ) & USART2_TX_BUFFER_MASK;
    while ( tmp == USART2_TxTail );
    USART2_TxBuf[tmp] = data;
    USART2_TxHead = tmp;
    UCSR2B |= (1<<UDRIE2);
}

char usart2_data_received( void )
{
    return ( USART2_RxHead != USART2_RxTail );
}

ISR(USART2_RX_vect)
{
    char data;
    unsigned char tmp;
    data = UDR2;
    tmp = ( USART2_RxHead + 1 ) & USART2_RX_BUFFER_MASK;
    USART2_RxHead = tmp;
    USART2_RxBuf[tmp] = data;
}

ISR(USART2_UDRE_vect)
{
    unsigned char tmp;

    if ( USART2_TxHead != USART2_TxTail )
    {
        #ifdef RS485_2_PORT
            RS485_2_PORT |= (1 << RS485_2_BIT);
        #endif /*RS485_2_PORT*/
        tmp = ( USART2_TxTail + 1 ) & USART2_TX_BUFFER_MASK;
        USART2_TxTail = tmp;
        UDR2 = USART2_TxBuf[tmp];
    }
    else
    {
        UCSR2B &= ~(1<<UDRIE2);
    }
}

#ifdef RS485_2_PORT
ISR(UART2_TXC_IRQ)
{
    RS485_2_PORT &= ~(1<<RS485_2_BIT);
}
#endif /*RS485_2_PORT*/
