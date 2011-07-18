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


#include "usart3.h"

/* Static Variables */
static char USART3_RxBuf[USART3_RX_BUFFER_SIZE];
static volatile char USART3_RxHead;
static volatile char USART3_RxTail;
static char USART3_TxBuf[USART3_TX_BUFFER_SIZE];
static volatile char USART3_TxHead;
static volatile char USART3_TxTail;

/* Initialize USART */
void usart3_init( void )
{
    #undef BAUD  // avoid compiler warning
    #define BAUD BAUD3
    #include <util/setbaud.h>
    UBRR3L = UBRRL_VALUE;
    UBRR3H = UBRRH_VALUE;
    UCSR3B = ( ( 1 << RXCIE3 ) | ( 1 << RXEN3 ) | ( 1 << TXEN3 ) );
    UCSR3C = (1<<UCSZ31)|(1<<UCSZ30);
#if USE3_2X
    UCSR3A |= (1 << U2X3);
#endif /*USE_2X*/
    USART3_RxTail = 0;
    USART3_RxHead = 0;
    USART3_TxTail = 0;
    USART3_TxHead = 0;

/* Init direction Pin for RS485 Driver, if RS485 is used */
#ifdef RS485_3_PORT
    UCSR3B |= (1 << TXCIE3);
    RS485_3_PORT &= ~(1<<RS485_3_BIT);
    RS485_3_DDR |= (1<<RS485_3_BIT);
#endif /*RS485_1_PORT*/
}

char usart3_getc( void )
{
    unsigned char tmp;

    while ( USART3_RxHead == USART3_RxTail );
    tmp = ( USART3_RxTail + 1 ) & USART3_RX_BUFFER_MASK;
    USART3_RxTail = tmp;
    return USART3_RxBuf[tmp];
}

void usart3_putc( char data )
{
    unsigned char tmp;
    tmp = ( USART3_TxHead + 1 ) & USART3_TX_BUFFER_MASK;
    while ( tmp == USART3_TxTail );
    USART3_TxBuf[tmp] = data;
    USART3_TxHead = tmp;
    UCSR3B |= (1<<UDRIE3);
}

char usart3_data_received( void )
{
    return ( USART3_RxHead != USART3_RxTail );
}


ISR(USART3_RX_vect)
{
    char data;
    unsigned char tmp;
    data = UDR3;
    tmp = ( USART3_RxHead + 1 ) & USART3_RX_BUFFER_MASK;
    USART3_RxHead = tmp;
    USART3_RxBuf[tmp] = data;
}

ISR(USART3_UDRE_vect)
{
    unsigned char tmp;

    if ( USART3_TxHead != USART3_TxTail )
    {
        #ifdef RS485_3_PORT
            RS485_3_PORT |= (1 << RS485_3_BIT);
        #endif /*RS485_3_PORT*/
        tmp = ( USART3_TxTail + 1 ) & USART3_TX_BUFFER_MASK;
        USART3_TxTail = tmp;
        UDR3 = USART3_TxBuf[tmp];
    }
    else
    {
        UCSR3B &= ~(1<<UDRIE3);
    }
}

#ifdef RS485_3_PORT
ISR(UART2_TXC_IRQ)
{
    RS485_3_PORT &= ~(1<<RS485_3_BIT);
}
#endif /*RS485_3_PORT*/
