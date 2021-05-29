410ULIB_STRING_OBJS := bcmp.o bcopy.o bzero.o memchr.o memcmp.o memset.o \
                      rindex.o strcasecmp.o strcat.o strchr.o strcmp.o  \
                      strcpy.o strcspn.o strdup.o strlen.o strncat.o    \
                      strncmp.o strncpy.o strpbrk.o strrchr.o strsep.o  \
                      strspn.o strstr.o strtok.o strtok_r.o 

410ULIB_STRING_OBJS := $(410ULIB_STRING_OBJS:%=$(410ULIBDIR)/string/%)

ALL_410UOBJS += $(410ULIB_STRING_OBJS)
410UCLEANS += $(410ULIBDIR)/libstring.a

$(410ULIBDIR)/libstring.a: $(410ULIB_STRING_OBJS)
