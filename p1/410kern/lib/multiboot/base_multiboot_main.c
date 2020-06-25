/*
 * base_multiboot_main.c
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * Copyright (c) 1996, 1998 University of Utah and the Flux Group.
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

#include <multiboot.h>
#include <base_vm.h>
#include <base_multiboot.h>
#include <x86/base_cpu.h>
#include <x86/proc_reg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <kerndebug.h>

struct multiboot_info boot_info;

extern int kernel_init();
extern int kernel_main(int argc, char *argv[], char *envp[]);
extern char **environ;

void
multiboot_main(unsigned int boot_info_pa)
{
	int argc = 0;
	char **argv = 0;
	int ret;

	/* Copy the multiboot_info structure into our pre-reserved area.
	   This avoids one loose fragment of memory that has to be avoided.  */
	boot_info = *(struct multiboot_info*)phystokv(boot_info_pa);

	//	kernel_init();

	/*
	 * Initialize the processor tables. ie default handlers etc.
	 */
	base_cpu_setup();

	/*
	 * Initialize the floating point unit.
	 */
	/*base_fpu_init();*/

	/* Initialize the memory allocator and find all available memory.  */
	base_multiboot_init_mem();

	/* Parse the command line into nice POSIX-like args and environment.  */
	base_multiboot_init_cmdline(&argc, &argv);

  SIMICS_SET_PROGRAM_NAME(argv[0]);

  /* Bad idea -- nwf; 20060306 */
	/* enable_interrupts(); */

	/* Invoke the main program. */
	ret = kernel_main(argc, argv, environ);
	printf( "base_multiboot_main.c: kernel main returned with code %d\n", 
                ret );
	while(1);
}
