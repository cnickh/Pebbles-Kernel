# This is a generic multi-file include so that stuents can (potentially)
# define their own libraries with their own user.mk files.
include $(patsubst lib%.a,$(STUULIBDIR)/%/user.mk,$(STUDENT_LIBS_EARLY))
include $(patsubst lib%.a,$(STUULIBDIR)/%/user.mk,$(STUDENT_LIBS_LATE))
