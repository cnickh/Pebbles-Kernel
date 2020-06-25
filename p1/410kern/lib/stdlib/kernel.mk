410KLIB_STDLIB_OBJS := atol.o environ.o getenv.o panic.o strtol.o strtoul.o \
												ctype.o
410KLIB_STDLIB_OBJS := $(410KLIB_STDLIB_OBJS:%=$(410KLIBDIR)/stdlib/%)

ALL_410KOBJS += $(410KLIB_STDLIB_OBJS)
410KCLEANS += $(410KLIBDIR)/libstdlib.a

$(410KLIBDIR)/libstdlib.a: $(410KLIB_STDLIB_OBJS)
	$(AR) rc $@ $^
