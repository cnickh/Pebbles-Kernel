/** @file kernel.c
 *  @brief A kernel with timer, keyboard, console support
 *
 *  This file contains the kernel's
 *  main() function.
 *
 *  It sets up the drivers, and starts the game.
 *
 *  @author Michael Berman (mberman)
 *  @bug No known bugs.
 */

/* -- Includes -- */

#include <410_reqs.h>
#include <console.h>


/* libc includes. */
#include <stdio.h>        /* for lprintf_kern() */

/* multiboot header file */
#include <multiboot.h>    /* for boot_info */

/* memory includes. */
#include <lmm.public.h>   /* for lmm_remove_free() */

/* x86 specific includes */
#include <x86/seg.h>      /* for install_user_segs() */
#include <x86/pic.h>      /* for pic_init() */
#include <x86/base_irq.h> /* for base_irq_master/slave */
#include <x86/proc_reg.h> /*enable_interrupts*/

/*
 * state for kernel memory allocation.
 */
extern lmm_t malloc_lmm;

/*
 * Info about system gathered by the boot loader
 */
extern struct multiboot_info boot_info;


/** @brief Kernel entrypoint.
 *
 *  This is the entrypoint for the kernel.  It simply sets up the
 *  drivers and passes control off to game_run().
 *
 * @return Does not return
 */
int kernel_main()
{
    /*
     * Tell the kernel memory allocator which memory it can't use.
     * It already knows not to touch kernel image.
     */

    /* Everything above 16M */
    lmm_remove_free( &malloc_lmm, (void*)USER_MEM_START, -8 - USER_MEM_START );

    /* Everything below 1M  */
    lmm_remove_free( &malloc_lmm, (void*)0, 0x100000 );

    /*
     * Install interrupt handlers here.
     */

    clear_console();

    handler_install();

    enable_interrupts();

    putbytes("# What's good\n",14);
    printf("# This is a test\b of printf()\n");
    printf("# Testing other stuff...\r");

    /*
     * initialize the PIC so that IRQs and
     * exception handlers don't overlap in the IDT.
     */
    pic_init( BASE_IRQ_MASTER_BASE, BASE_IRQ_SLAVE_BASE );

    while (1) {
      continue;
    }

    return 0;
}
