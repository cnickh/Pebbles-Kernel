/*
 * string.h
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1994-1998, 2000 University of Utah and the Flux Group.
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
#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
#define NULL 0
#endif

int strlen(const char *__s);
char *strcpy(char *__dest, const char *__src);
char *strncpy(char *__dest, const char *__src, int __n);
char *strdup(const char *__s);
char *strcat(char *__dest, const char *__src);
char *strncat(char *__dest, const char *__src, int __n);
int strcmp(const char *__a, const char *__b);
int strncmp(const char *__a, const char *__b, int __n);

char *strchr(const char *__s, int __c);
char *strrchr(const char *__s, int __c);
char *strstr(const char *__haystack, const char *__needle);
char *strtok(char *__s, const char *__delim);
char *strtok_r(char *__s, const char *__delim, char **__last);
char *strpbrk(const char *__s1, const char *__s2);
int strspn(const char *__s1, const char *__s2);
int strcspn(const char *__s1, const char *__s2);

void *memmove(void *__to, const void *__from, unsigned int __n);
void *memset(void *__to, int __ch, unsigned int __n);

void *memcpy(void *__to, const void *__from, unsigned int __n);
int memcmp(const void *s1v, const void *s2v, int size);

void * memchr(const void *b, int c, int len);

/*
 * Traditional BSD string functions,
 * not defined in ANSI or POSIX but included in Unix CAE.
 * It is preferable to use the ANSI functions in <string.h> in new code.
 */

int bcmp(const void *s1, const void *s2, int n);
void bcopy(const void *from, void *to, int n);
void bzero(void *to, int n);

char *rindex(const char *s, int c);

int strcasecmp(const char *s1, const char *s2);

/* This isn't in the CAE manual... */
char *strsep(char **stringp, const char *delim);

#endif /* _STRING_H */
