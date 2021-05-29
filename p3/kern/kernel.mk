#
# You should only need to modify config.mk to get things to run
#
# directly adding kernel objs here may well break things
#
# NOTE TO TAs: This file must be included *AFTER* the 410kern kernel.mk
# file as we depend on its idea of KLIBPATH

STUKOBJS = $(KERNEL_OBJS:%=$(STUKDIR)/%)
ALL_STUKOBJS += $(STUKOBJS)

STUKCLEANS += $(STUKDIR)/partial_kernel.o

$(STUKDIR)/partial_kernel.o : $(STUKOBJS)
	$(LD) -r -static $(LDFLAGS) -o $@ $^
