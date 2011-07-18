#ifndef USART1_H
#define USART1_H 1
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


#ifndef BAUD1
    #error "The Parameter BAUD is not defined in the Project.\
    Please add the Parameter to config.h\
    You can find an Example on wiki.elektronik-projekt.de"
#endif  /*BAUD1*/

/* UART Buffer Defines */
#ifndef USART1_RX_BUFFER_SIZE
    #error "The Parameter USART1_RX_BUFFER_SIZE is not defined in the Project.\
    Please add the Parameter to config.h.\
    You can find an Example on wiki.elektronik-projekt.de"
#endif /*USART1_RX_BUFFER_SIZE*/

#ifndef USART1_TX_BUFFER_SIZE
    #error "The Parameter USART1_TX_BUFFER_SIZE is not defined in the Project.\
    Please add the Parameter to config.h.\
    You can find an Example on wiki.elektronik-projekt.de"
#endif /*USART1_TX_BUFFER_SIZE*/

#define USART1_RX_BUFFER_MASK ( USART1_RX_BUFFER_SIZE - 1 )
#define USART1_TX_BUFFER_MASK ( USART1_TX_BUFFER_SIZE - 1 )
#if ( USART1_RX_BUFFER_SIZE & USART1_RX_BUFFER_MASK )
    #error RX buffer size is not a power of 2
#endif
#if ( USART1_TX_BUFFER_SIZE & USART1_TX_BUFFER_MASK )
    #error TX buffer size is not a power of 2
#endif

/**----------------------------------
 * Prototypes
 *----------------------------------*/

/**----------------------------------
 * @brief   Initialize USART
 * @param   void
 * @return  void
 *----------------------------------*/
void usart1_init( void );

/**----------------------------------
 * @brief   Receives Char from USART Buffer
 * @param   void
 * @return  char
 *----------------------------------*/
char usart1_getc( void );

/**----------------------------------
 * @brief   Sends Char to USART Buffer
 * @param   Char to send
 * @return  void
 *----------------------------------*/
void usart1_putc( char data );

/**----------------------------------
 * @brief   Test if received char is in Buffer
 * @param   void
 * @return  Return 0 (FALSE) if the receive buffer is empty
 *----------------------------------*/
char usart1_data_received( void );

#endif /* USART1_H */
