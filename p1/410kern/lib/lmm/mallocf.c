/*
 * mallocf.c
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 * Joey Echeverria (jge)
 */

/*
 * Copyright (c) 2000 University of Utah and the Flux Group.
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

/*
 * Standard C malloc functions built on top of lmm but exposing the lmm 
 * flags.
 * Keeps track of the size of the object for you.
 *
 * Can be combined with various lmm adaptors to get thread-safety,
 * caching, etc.
 */
#include <malloc.h>

#include <lmm.public.h>
#include <lmm.malloc.h>
#include <string.h>

#include <bitops.h>

void *malloc_flags(size_t size, lmm_flags_t flags)
{
        unsigned int *chunk;
	chunk = out_alloc(size + sizeof(unsigned int), flags);
        if (chunk) 
                *chunk++ = size;
        return chunk;
}

void *memalign_flags(size_t alignment, size_t size, lmm_flags_t flags)
{
        unsigned int shift = log2(alignment);
        unsigned int *chunk;
	chunk = out_alloc_aligned( size + sizeof(unsigned int), flags, shift, 
                                   (1 << shift) - sizeof(unsigned int));
        if (chunk) 
                *chunk++ = size;
        return chunk;
}

void free_flags(void *v_chunk)
{
        unsigned int size;
	unsigned int *chunk = (unsigned int *)v_chunk;
	/* Posix says free of NULL does nothing */
	if (!chunk)
		return;
        chunk -= 1;
	size = *chunk;
	out_free(chunk, size + sizeof(*chunk));
}
