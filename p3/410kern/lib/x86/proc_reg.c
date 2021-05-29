/*
 * proc_reg.c
 *
 * Functions for reading and writing processor registers
 * CMU_OS
 * Zachary Anderson(zra)
 */

#include <x86/proc_reg.h>


inline void set_eflags(unsigned eflags)
{
        asm volatile("\
                pushl %0;\
                popfl" : : "r" (eflags));
}

inline void cld(void) { asm("cld"); }
inline void std(void) { asm("std"); }
inline void clts(void) { asm("clts"); }

inline unsigned short get_cs(void)
{
        unsigned short cs;
        asm volatile("movw %%cs,%w0" : "=r" (cs));
        return cs;
}
 
inline unsigned short get_ds(void)
{
        unsigned short ds;
        asm volatile("movw %%ds,%w0" : "=r" (ds));
        return ds;
}
inline void set_ds(unsigned short ds)
{
        asm volatile("movw %w0,%%ds" : : "r" (ds));
}

inline unsigned short get_es(void)
{       
        unsigned short es;
        asm volatile("movw %%es,%w0" : "=r" (es));
        return es;
}
inline void set_es(unsigned short es)
{
        asm volatile("movw %w0,%%es" : : "r" (es));
}
   
inline unsigned short get_fs(void)
{
        unsigned short fs;
        asm volatile("movw %%fs,%w0" : "=r" (fs));
        return fs;
}
inline void set_fs(unsigned short fs)
{
        asm volatile("movw %w0,%%fs" : : "r" (fs));
}
 
inline unsigned short get_gs(void)
{
        unsigned short gs;
        asm volatile("movw %%gs,%w0" : "=r" (gs));
        return gs;
}
inline void set_gs(unsigned short gs)
{
        asm volatile("movw %w0,%%gs" : : "r" (gs));
}

inline unsigned short get_ss(void)
{
        unsigned short ss;
        asm volatile("movw %%ss,%w0" : "=r" (ss));
        return ss;
}
inline void set_ss(unsigned short ss)
{
        asm volatile("movw %w0,%%ss" : : "r" (ss));
}
