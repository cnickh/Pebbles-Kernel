###################### LOCAL BUILD TARGETS ############################

410KCLEANS += $(410KDIR)/partial_kernel.o

$(410KDIR)/partial_kernel.o : $(410KDIR)/ref_kernel.o
	cp $< $@

###################### FULL BUILD TARGETS ############################

FINALTARGETS=kernel
FINALVERYCLEANS=$(FINALTARGETS)
FINALCLEANS =	$(FINALTARGETS:%=%.strip) \
							$(FINALTARGETS:%=%.gz)

$(patsubst %,$(BUILDDIR)/%.o,$(FINALTARGETS)) : $(BUILDDIR)/%.o : \
											$(410KDIR)/partial_%.o \
											$(410KLIBS)
	mkdir -p $(BUILDDIR)
	$(LD) -r -static $(KLDFLAGS) -o $@ $^

$(FINALTARGETS) : %: $(BUILDDIR)/%.o $(BUILDDIR)/user_apps.o
	$(LD) -T kernel.lds $(KLDFLAGS) -o $@ $^

$(patsubst %,%.strip,$(FINALTARGETS)) : %.strip : %
	objcopy -g $< $@

$(patsubst %,%.gz,$(FINALTARGETS)) : %.gz : %.strip
	gzip -c $< > $@

bootfd.img.gz:
	@echo file bootfd.img.gz missing
	@false

bootfd.img: $(FINALTARGETS:%=%.gz) bootfd.img.gz $(MTOOLSRC)
	gzip -cd bootfd.img.gz > bootfd.img
	MTOOLSRC=$(MTOOLSRC) mcopy -o $(FINALTARGETS:%=%.gz) K:/boot/

$(MTOOLSRC):
	echo "drive K: file=\"$(PROJROOT)/bootfd.img\" " > $@
