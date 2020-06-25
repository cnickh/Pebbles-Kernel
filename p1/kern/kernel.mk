#
# You should only need to modify config.mk to get things to run
#
# directly adding kernel objs here may well break things
#

STUKOBJS_COMMON = $(COMMON_OBJS:%=$(STUKDIR)/%)
STUKOBJS = $(KERN_GAME_OBJS:%=$(STUKDIR)/%)

ALL_STUKOBJS += $(STUKOBJS_COMMON) $(STUKOBJS)

STUKCLEANS += $(STUKDIR)/partial_game.o $(STUKDIR)/partial_410test.o

$(STUKDIR)/partial_game.o : $(STUKOBJS) $(STUKOBJS_COMMON)
	$(LD) -r -static $(LDFLAGS) -o $@ $^

$(STUKDIR)/partial_410test.o : $(STUKOBJS_COMMON)
	$(LD) -r -static $(LDFLAGS) -o $@ $^
