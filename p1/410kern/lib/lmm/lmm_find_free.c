/*
 * lmm_find_free.c
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1995, 1998 University of Utah and the Flux Group.
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

#include "lmm.h"

void lmm_find_free(lmm_t *lmm, unsigned int *inout_addr,
		   unsigned int *out_size, lmm_flags_t *out_flags)
{
	struct lmm_region *reg;
	unsigned int start_addr = (*inout_addr + ALIGN_MASK) & ~ALIGN_MASK;
	unsigned int lowest_addr = (unsigned int)-1;
	int lowest_size = 0;
	unsigned lowest_flags = 0;

	for (reg = lmm->regions; reg; reg = reg->next)
	{
		struct lmm_node *node;

		if ((reg->nodes == 0)
		    || (reg->max <= start_addr)
		    || (reg->min > lowest_addr))
			continue;

		for (node = reg->nodes; node; node = node->next)
		{
			assert((unsigned int)node >= reg->min);
			assert((unsigned int)node < reg->max);

			if ((unsigned int)node >= lowest_addr)
				break;
			if ((unsigned int)node + node->size > start_addr)
			{
				if ((unsigned int)node > start_addr)
				{
					lowest_addr = (unsigned int)node;
					lowest_size = node->size;
				}
				else
				{
					lowest_addr = start_addr;
					lowest_size = node->size
						- (lowest_addr - (unsigned int)node);
				}
				lowest_flags = reg->flags;
				break;
			}
		}
	}

	*inout_addr = lowest_addr;
	*out_size = lowest_size;
	*out_flags = lowest_flags;
}

