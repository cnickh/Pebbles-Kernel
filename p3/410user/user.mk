################# TARGET-SPECIFIC RULES #################
$(410UDIR)/exec2obj.dep: INCLUDES=$(KINCLUDES) -I-
$(410UDIR)/exec2obj.dep: CFLAGS=-m32 -Wall -Werror

$(410UDIR)/exec2obj: $(410UDIR)/exec2obj.c
	$(CC) -m32 $(KINCLUDES) -I- -Wall -Werror -o $@ $^

ifeq (0,$(words $(filter %clean,$(MAKECMDGOALS))))
-include $(410UDIR)/exec2obj.dep
endif

410UCLEANS+=$(410UDIR)/exec2obj $(410UDIR)/exec2obj.dep

$(BUILDDIR)/user_apps.S: $(410UDIR)/exec2obj $(PROGS:%=$(BUILDDIR)/%)
	( cd $(BUILDDIR); $(PROJROOT)/$(410UDIR)/exec2obj $(PROGS) ) > $@

$(BUILDDIR)/user_apps.o: $(BUILDDIR)/user_apps.S
	$(AS) --32 -o $@ $<

include $(410ULIBDIR)/user.mk
include $(410UDIR)/$(UPROGDIR)/progs.mk
