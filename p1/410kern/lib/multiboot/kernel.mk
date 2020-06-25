410KLIB_MULTIBOOT_OBJS := multiboot.o base_multiboot_main.o \
													base_multiboot_init_mem.o \
													base_multiboot_init_cmdline.o \
													base_stack.o

410KLIB_MULTIBOOT_OBJS := $(410KLIB_MULTIBOOT_OBJS:%=$(410KLIBDIR)/multiboot/%)

ALL_410KOBJS += $(410KLIB_MULTIBOOT_OBJS)
410KCLEANS += $(410KLIBDIR)/MultiBoot.o

# Override the usual .o rule
$(410KLIBDIR)/MultiBoot.o: $(410KLIB_MULTIBOOT_OBJS)
	$(LD) -r -o $@ $(LDFLAGS) $^
