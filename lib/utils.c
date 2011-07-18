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

#include "utils.h"

/**----------------------------------
 * @brief Send a string to function *f
 * @param *f function pointer
 * @param *s string
 * @return void
 *----------------------------------*/

void write(void (*f)(char), const char *s )
{
    while (*s)
        f(*s++);
}

/**----------------------------------
 * @brief Send a string to function *f with Line End
 * @param *f function pointer
 * @param *s string
 * @return void
 *----------------------------------*/

void writeln(void (*f)(char), const char *s )
{
    while (*s)
        f(*s++);
#if LINE_END==1 || LINE_END==2
    f('\r');
#endif
#if LINE_END==0 || LINE_END==2
    f('\n');
#endif
}

/**----------------------------------
 * @brief Send a string from Flash to function *f
 * @param *f function pointer
 * @param *s const string
 * @return void
 *----------------------------------*/

void write_p(void (*f)(char), const char *progmem_s )
{
    register char c;

    while ( (c = pgm_read_byte(progmem_s++)) )
        f(c);
}

/**----------------------------------
 * @brief Send a string from Flash to function *f with Line End
 * @param *f function pointer
 * @param *s const string
 * @return void
 *----------------------------------*/

void writeln_p(void (*f)(char), const char *progmem_s )
{
    register char c;

    while ( (c = pgm_read_byte(progmem_s++)) )
        f(c);
#if LINE_END==1 || LINE_END==2
    f('\r');
#endif
#if LINE_END==0 || LINE_END==2
    f('\n');
#endif
}
