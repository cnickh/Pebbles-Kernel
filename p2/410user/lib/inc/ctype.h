/*
 * ctype.h
 * Modified for 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1994-1996, 1998 University of Utah and the Flux Group.
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
#ifndef _CTYPE_H
#define _CTYPE_H

extern int isascii(int c);
extern int iscntrl(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int islower(int c);
extern int isprint(int c);
extern int isspace(int c);
extern int isupper(int c);
extern int isxdigit(int c);
extern int isalpha(int c);
extern int isalnum(int c);
extern int ispunct(int c);
extern int toascii(int c);
extern int toupper(int c);
extern int tolower(int c);

#endif /* _CTYPE_H */
