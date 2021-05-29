/** @file kernel.c
 *  @brief An initial kernel.c
 *
 *  You should initialize things in kernel_main()
 *
 *  @author Harry Q. Bovik (hqbovik)
 *  @author Fred Hacker (fhacker)
 *  @bug No known bugs.
 */

/* -- Includes -- */

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
 *  This is the entrypoint for your kernel.
 * 
 *  @return Should not return
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
     * initialize the PIC so that IRQs and
     * exception handlers don't overlap in the IDT.
     */
    pic_init( BASE_IRQ_MASTER_BASE, BASE_IRQ_SLAVE_BASE );

    /*
     * When kernel_main() begins, interrupts are DISABLED.
     * You should delete this comment, and enable them --
     * when you are ready.
     */

    lprintf_kern( "Hello from a brand new kernel!" );

    while (1)
        continue;

    return 0;
}
