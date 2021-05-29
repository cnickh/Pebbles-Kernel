/*
 * stdio.h
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1994-2001 University of Utah and the Flux Group.
 * All rights reserved.
 * 
 * This file is part of the Flux OSKit.  The OSKit is free software, also known
 * as "open source;" you can redistribute it and/or modify it under the terms
 * of the GNU General Public License (GPL), version 2, as published by the Free
 * Software Foundation (FSF).  To explore alternate licensing terms, contact
 * the University of Utah at csl-dist@cs.utah.edu or +1-801-585-3271.
 * 
 * The OSKit is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GPL for more details.  You should have
 * received a copy of the GPL along with the OSKit; see the file COPYING.  If
 * not, write to the FSF, 59 Temple Place #330, Boston, MA 02111-1307, USA.
 */
#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

/* This is a very naive standard I/O implementation
   which simply chains to the low-level I/O routines
   without doing any buffering or anything.  */

#ifndef NULL
#define NULL 0
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#ifndef EOF
#define EOF -1
#endif

#ifndef BUFSIZ
#define BUFSIZ	1024
#endif

int putchar(int __c);
int puts(const char *__str);
int printf(const char *__format, ...);
int vprintf(const char *__format, va_list __vl);
int sprintf(char *__dest, const char *__format, ...);
int snprintf(char *__dest, int __size, const char *__format, ...);
int vsprintf(char *__dest, const char *__format, va_list __vl);
int vsnprintf(char *__dest, int __size, const char *__format, va_list __vl);
int sscanf(const char *__str, const char *__format, ...);

/* CMU_OS additions */

void lprintf_kern( char *fmt, ... );
void lprintf( char *fmt, ... );

#endif /* _STDIO_H */
