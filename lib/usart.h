#ifndef USART0_H
#define USART0_H 1
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

#include <avr/version.h>

#if __AVR_LIBC_VERSION__ < 10602UL
#error The USART Module needs avr-libc Version 1.6.2 or later
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <config.h>


/* UART Buffer Defines */
#ifndef USART0_RX_BUFFER_SIZE
    #error "The Parameter USART0_RX_BUFFER_SIZE is not defined in the Project.\
    Please add the Parameter to config.h.\
    You can find an Example on wiki.elektronik-projekt.de"
#endif /*USART0_RX_BUFFER_SIZE*/

#ifndef USART0_TX_BUFFER_SIZE
    #error "The Parameter USART0_TX_BUFFER_SIZE is not defined in the Project.\
    Please add the Parameter to config.h.\
    You can find an Example on wiki.elektronik-projekt.de"
#endif /*USART0_TX_BUFFER_SIZE*/

#define USART0_RX_BUFFER_MASK ( USART0_RX_BUFFER_SIZE - 1 )
#define USART0_TX_BUFFER_MASK ( USART0_TX_BUFFER_SIZE - 1 )
#if ( USART0_RX_BUFFER_SIZE & USART0_RX_BUFFER_MASK )
    #error RX buffer size is not a power of 2
#endif
#if ( USART0_TX_BUFFER_SIZE & USART0_TX_BUFFER_MASK )
    #error TX buffer size is not a power of 2
#endif

/*------------------------------------------------------------------------------
 * Fixes for USART(0)
 *----------------------------------------------------------------------------*/
#if defined (UDR)
#define UDR0    UDR
#define UBRR0L  UBRRL
#define UBRR0H  UBRRH
#define UCSR0A  UCSRA
#define UCSR0B  UCSRB
#define UCSR0C  UCSRC
#define RXCIE0  RXCIE
#define TXCIE0  TXCIE
#define RXEN0   RXEN
#define TXEN0   TXEN
#define U2X0    U2X
#define UCSZ00  UCSZ0
#define UCSZ01  UCSZ1
#define UDRIE0  UDRIE
#endif

#if defined(SIG_USART_RECV)
    #define UART0_RECV_IRQ SIG_USART_RECV
    #define UART0_DATA_IRQ SIG_USART_DATA
    #define UART0_TXC_IRQ SIG_USART_TRANS
#elif defined(SIG_USART0_RECV)
    #define UART0_RECV_IRQ SIG_USART0_RECV
    #define UART0_DATA_IRQ SIG_USART0_DATA
    #define UART0_TXC_IRQ SIG_USART0_TRANS
#elif defined(SIG_UART0_RECV)
    #define UART0_RECV_IRQ SIG_UART0_RECV
    #define UART0_DATA_IRQ SIG_UART0_DATA
    #define UART0_TXC_IRQ SIG_UART0_TRANS
#elif defined(SIG_UART_RECV)
    #define UART0_RECV_IRQ SIG_UART_RECV
    #define UART0_DATA_IRQ SIG_UART_DATA
    #define UART0_TXC_IRQ SIG_UART_TRANS
#else
    #define UART0_RECV_IRQ SIG_USART_RECV
    #define UART0_DATA_IRQ SIG_USART_DATA
    #define UART0_TXC_IRQ SIG_USART_TRANS
#endif

/**----------------------------------
 * Prototypes
 *----------------------------------*/

/**----------------------------------
 * @brief   Initialize USART
 * @param   void
 * @return  void
 *----------------------------------*/
void usart0_init( void );

/**----------------------------------
 * @brief   Receives Char from USART Buffer
 * @param   void
 * @return  char
 *----------------------------------*/
char usart0_getc( void );

/**----------------------------------
 * @brief   Sends Char to USART Buffer
 * @param   Char to send
 * @return  void
 *----------------------------------*/
void usart0_putc( char data );

/**----------------------------------
 * @brief   Test if received char is in Buffer
 * @param   void
 * @return  Return 0 (FALSE) if the receive buffer is empty
 *----------------------------------*/
char usart0_data_received( void );

#endif /* USART_H */
