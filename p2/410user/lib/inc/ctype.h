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

inline int isascii(int c);
inline int iscntrl(int c);
inline int isdigit(int c);
inline int isgraph(int c);
inline int islower(int c);
inline int isprint(int c);
inline int isspace(int c);
inline int isupper(int c);
inline int isxdigit(int c);
inline int isalpha(int c);
inline int isalnum(int c);
inline int ispunct(int c);
inline int toascii(int c);
inline int toupper(int c);
inline int tolower(int c);

#endif /* _CTYPE_H */
