/* The 15-410 kernel.
 * magic_break.h
 *
 * A macro for creating a magic breakpoint.
 *
 */

#ifndef _MAGIK_BREAK_H
#define _MAGIK_BREAK_H

#define MAGIC_BREAK asm("pushl %%ebx;            \
                         movl $0x2badd00d,%%ebx; \
                         xchg %%bx,%%bx;         \
                         popl %%ebx" : : )

#define SIM_chkpt_two() asm( "pushl %%ebx;\
                              movl $0xabadd00d, %%ebx;\
                              xchg %%ebx, %%ebx;\
                              popl %%ebx" : : )

#endif /* _MAGIK_BREAK_H */
