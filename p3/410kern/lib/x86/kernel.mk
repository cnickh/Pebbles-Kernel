410KLIB_X86_OBJS:= base_cpu_init.o base_cpu_load.o base_fpu_init.o            \
                   base_gdt.o base_gdt_init.o base_gdt_load.o base_idt.o      \
                   base_idt_load.o base_irq.o base_irq_default_handler.o      \
                   base_irq_init.o base_irq_inittab.o base_irq_softint.o      \
                   base_irq_softint_handler.o base_trap.o                     \
                   base_trap_default_handler.o base_trap_ignore_handler.o     \
                   base_trap_init.o base_trap_inittab.o base_tss.o            \
                   base_tss_init.o base_tss_load.o gate_init.o pic.o seg.o    \
                   trap_dump.o trap_dump_panic.o proc_reg.o proc_reg_cr0.o    \
                   keyhelp.o sound.o
410KLIB_X86_OBJS := $(410KLIB_X86_OBJS:%=$(410KLIBDIR)/x86/%)

ALL_410KOBJS += $(410KLIB_X86_OBJS)
410KCLEANS += $(410KLIBDIR)/libx86.a

$(410KLIBDIR)/libx86.a: $(410KLIB_X86_OBJS)
	$(AR) rc $@ $^
