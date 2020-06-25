/*
 * lmm.public.h
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1995-1996, 1998 University of Utah and the Flux Group.
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
 * Public header file for the List Memory Manager.
 */

#ifndef _LMM_PUBLIC_H_
#define _LMM_PUBLIC_H_

typedef unsigned int lmm_flags_t;
typedef int          lmm_pri_t;

/* The contents of these structures are opaque to users.  */
typedef struct lmm_region
{
	struct lmm_region *next;

	/* List of free memory blocks in this region.  */
	struct lmm_node *nodes;

	/* Virtual addresses of the start and end of the memory region.  */
	unsigned int min;
	unsigned int max;

	/* Attributes of this memory.  */
	lmm_flags_t flags;

	/* Allocation priority of this region with respect to other regions.  */
	lmm_pri_t pri;

	/* Current amount of free space in this region in bytes.  */
	int free;
} lmm_region_t;

typedef struct lmm
{
	struct lmm_region *regions;
} lmm_t;

#define LMM_INITIALIZER { 0 }

void lmm_init(lmm_t *lmm);
void lmm_add_region(lmm_t *lmm, lmm_region_t *lmm_region,
		    void *addr, int size,
		    lmm_flags_t flags, lmm_pri_t pri);
void lmm_add_free(lmm_t *lmm, void *block, int size);
void lmm_remove_free(lmm_t *lmm, void *block, int size);
void *lmm_alloc(lmm_t *lmm, int size, lmm_flags_t flags);
void *lmm_alloc_aligned(lmm_t *lmm, int size, lmm_flags_t flags,
			int align_bits, unsigned int align_ofs);
void *lmm_alloc_page(lmm_t *lmm, lmm_flags_t flags);
void *lmm_alloc_gen(lmm_t *lmm, int size, lmm_flags_t flags,
		    int align_bits, unsigned int align_ofs,
		    int bounds_min, int bounds_max);
int lmm_avail(lmm_t *lmm, lmm_flags_t flags);
void lmm_find_free(lmm_t *lmm, unsigned int *inout_addr,
		   unsigned int *out_size, lmm_flags_t *out_flags);
void lmm_free(lmm_t *lmm, void *block, int size);
void lmm_free_page(lmm_t *lmm, void *block);

/* Only available if debugging turned on.  */
void lmm_dump(lmm_t *lmm);
void lmm_stats(lmm_t *lmm);

#endif /* _LMM_PUBLIC_H_ */
