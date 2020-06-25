/*
 * seg.c
 * Modified for use in 15-410 at CMU
 * Zachary Anderson(zra)
 */

/*
 * I assume this is smuckle's code as opposed to oskit.
 * It will come in handy anyway, since these functions
 * are used in the reference kernel, and don't seem to
 * be provided by oskit. These should all be redone to
 * use the structs provided by oskit.
 */

#include <x86/seg.h>
#include <x86/proc_reg.h>
#include <stdio.h>
#include <page.h>
#include <multiboot.h>    /* for boot_info */

/*
 * Info about system gathered by the boot loader
 */
extern struct multiboot_info boot_info;

const char *system_seg_types[] = {"Reserved", "16-Bit TSS (Available)",
				  "Local Descriptor Table (LDT)",
				  "16-Bit TSS (Busy)", "16-Bit Call Gate",
				  "Task Gate", "16-Bit Interrupt Gate",
				  "16-Bit Trap Gate", "Reserved",
				  "32-Bit TSS (Available)", "Reserved",
				  "32-Bit TSS (Busy)", "32-Bit Call Gate",
				  "Reserved", "32-Bit Interrupt Gate",
				  "32-Bit Trap Gate"};

const char *code_data_seg_types[] = {"Data: Read-Only",
				     "Data: Read-Only, Accessed",
				     "Data: Read/Write",
				     "Data: Read/Write, Accessed",
				     "Data: Read-Only, Expand-Down",
				     "Data: Read-Only, Expand-Down, Accessed",
				     "Data: Read/Write, Expand-Down",
				     "Data: Read/Write, Expand-Down, Accessed",
				     "Code: Execute-Only",
				     "Code: Execute-Only, Accessed",
				     "Code: Execute/Read",
				     "Code: Execute/Read, Accessed",
				     "Code: Execute-Only, Conforming",
				     "Code: Execute-Only, Conforming, Accessed",
				     "Code: Execute/Read-Only, Conforming",
				     "Code: Execute/Read-Only, Conforming, Accessed"};

void set_esp0(void* new_esp0)
{
  struct pseudo_descriptor gdt_location;
  struct x86_desc* gdt;
  struct x86_tss *proc_tss = NULL;

  get_gdt(&gdt_location);
  gdt = (struct x86_desc*)gdt_location.linear_base;
  proc_tss = (struct x86_tss *)(gdt[1].base_low + (gdt[1].base_med << 16) +
		    (gdt[1].base_high << 24));
  proc_tss->esp0 = (int)new_esp0;
}

void* get_esp0()
{
  struct pseudo_descriptor gdt_location;
  struct x86_desc* gdt;
  struct x86_tss *proc_tss = NULL;

  get_gdt(&gdt_location);
  gdt = (struct x86_desc*)gdt_location.linear_base;
  proc_tss = (struct x86_tss *)(gdt[1].base_low + (gdt[1].base_med << 16) +
		    (gdt[1].base_high << 24));
  return (void*)(proc_tss->esp0);
}

/*
 * returns a pointer to the beginning of the installed IDT.
 */
void *sidt(void)
{
    unsigned int ptr[2];
    asm ("sidt (%0)": :"p" (((char *) ptr)+2));
    return (void *) ptr[1];
}

/* Fill a segment descriptor.  */
inline void
fill_descriptor(struct x86_desc *desc, unsigned base, unsigned limit,
                unsigned char access, unsigned char sizebits)
{
        if (limit > 0xfffff)
        {
                limit >>= 12;
                sizebits |= SZ_G;
        }
        desc->limit_low = limit & 0xffff;
        desc->base_low = base & 0xffff;
        desc->base_med = (base >> 16) & 0xff;
        desc->access = access | ACC_P;
        desc->limit_high = limit >> 16;
        desc->granularity = sizebits;
        desc->base_high = base >> 24;
}

/* Set the base address in a segment descriptor.  */
inline void
fill_descriptor_base(struct x86_desc *desc, unsigned base)
{
        desc->base_low = base & 0xffff;
        desc->base_med = (base >> 16) & 0xff;
        desc->base_high = base >> 24;
}

/* Set the limit in a segment descriptor.  */
inline void
fill_descriptor_limit(struct x86_desc *desc, unsigned limit)
{
        if (limit > 0xfffff)
        {
                limit >>= 12;
                desc->granularity |= SZ_G;
        }
        else
                desc->granularity &= ~SZ_G;
        desc->limit_low = limit & 0xffff;
        desc->limit_high = limit >> 16;
}

int machine_phys_frames(void)
{
  int memsize;

  asm volatile("push %%esi;\
                push %%ebp;\
                movl %[memsizein],%%esi;\
                movl $0xbeefd00d, %%ebx;\
                xchg %%bx,%%bx;\
                movl %%esi,%[memsizeout];\
                pop %%ebp;\
                pop %%esi;\
" : [memsizeout] "=r" (memsize) : [memsizein] "r" (boot_info.mem_upper+1024) : "%ebx", "%esi");
  return (1024*memsize / PAGE_SIZE);
}

