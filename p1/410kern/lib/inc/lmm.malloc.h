/*
 * lmm.malloc.h
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
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
 * This header file is useful for units which interpose on the lmm
 * interface.
 */

#ifndef _LMM_MALLOC_H
#define _LMM_MALLOC_H

#include <lmm.public.h>

extern lmm_t malloc_lmm;

void out_add_region(lmm_region_t *lmm_region,
                    void *addr, unsigned int size,
                    lmm_flags_t flags, lmm_pri_t pri);
void out_add_free(void *block, unsigned int size);
void out_remove_free(void *block, unsigned int size);
void *out_alloc(unsigned int size, lmm_flags_t flags);
void *out_alloc_aligned(unsigned int size, lmm_flags_t flags,
                        int align_bits, unsigned int align_ofs);
void *out_alloc_page(lmm_flags_t flags);
void *out_alloc_gen(unsigned int size, lmm_flags_t flags,
                    int align_bits, unsigned int align_ofs,
                    unsigned int bounds_min, unsigned int bounds_max);
unsigned int out_avail(lmm_flags_t flags);
void out_find_free(unsigned int *inout_addr,
                   unsigned int *out_size, lmm_flags_t *out_flags);
void out_free(void *block, unsigned int size);
void out_free_page(void *block);

/* Only available if debugging turned on.  */
void out_dump(void);
void out_stats(void);

#endif /* _LMM_MALLOC_H */
