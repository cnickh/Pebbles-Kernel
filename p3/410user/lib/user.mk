410USER_LIBS_EARLY_MAKEFILES=\
$(patsubst lib%.a,$(410ULIBDIR)/%/user.mk,$(410USER_LIBS_EARLY))

ifneq (,$(410USER_LIBS_EARLY_MAKEFILES))
include $(410USER_LIBS_EARLY_MAKEFILES)
endif
include $(patsubst lib%.a,$(410ULIBDIR)/%/user.mk,$(410USER_LIBS_LATE))
