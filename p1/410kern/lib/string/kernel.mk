410KLIB_STRING_OBJS:= bcmp.o bcopy.o bzero.o memchr.o memcmp.o memset.o \
                      rindex.o strcasecmp.o strcat.o strchr.o strcmp.o  \
                      strcpy.o strcspn.o strdup.o strlen.o strncat.o    \
                      strncmp.o strncpy.o strpbrk.o strrchr.o strsep.o  \
                      strspn.o strstr.o strtok.o strtok_r.o 
410KLIB_STRING_OBJS:= $(410KLIB_STRING_OBJS:%=$(410KLIBDIR)/string/%)

ALL_410KOBJS += $(410KLIB_STRING_OBJS)
410KCLEANS += $(410KLIBDIR)/libstring.a

$(410KLIBDIR)/libstring.a: $(410KLIB_STRING_OBJS)
	$(AR) rc $@ $^
