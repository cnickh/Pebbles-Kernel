include $(410KLIBDIR)/multiboot/kernel.mk
include $(patsubst lib%.a,$(410KLIBDIR)/%/kernel.mk,$(410KERNEL_LIBS))
