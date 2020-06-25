/**
 * The 15-410 kernel project
 * @name kerndebug.h
 *
 * Functions related to using
 * Simics for debugging the kernel
 * and user processes.
 */

#ifndef __KERNDEBUG_H
#define __KERNDEBUG_H

#define SIMICS_SET_PROGRAM_NAME(str) \
  asm volatile("pushl %%eax;\
                pushl %%ebx;\
                movl %0, %%eax;\
                movl $0xb00710ad, %%ebx;\
                xchg %%bx,%%bx;\
                popl %%ebx;\
                popl %%eax" : : "m"(str) : "%eax", "%ebx");


#define MAGIC_BREAK asm("pushl %%ebx; movl $0x2badd00d,%%ebx; xchg %%bx,%%bx; popl %%ebx" : : )

void SIM_register_user_proc( void *cr3, char *fname );
void SIM_register_user_from_parent( void *child_cr3, void *parent_cr3 );
void SIM_unregister_user_proc( void *cr3 );
void SIM_switch( unsigned int cr3 );
void SIM_halt();
void SIM_beep();

#endif
