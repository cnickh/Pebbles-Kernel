410ULIB_STDLIB_OBJS := atol.o environ.o exit.o getenv.o panic.o strtol.o strtoul.o \
											ctype.o
410ULIB_STDLIB_OBJS := $(410ULIB_STDLIB_OBJS:%=$(410ULIBDIR)/stdlib/%)

ALL_410UOBJS += $(410ULIB_STDLIB_OBJS)
410UCLEANS += $(410ULIBDIR)/libstdlib.a

$(410ULIBDIR)/libstdlib.a: $(410ULIB_STDLIB_OBJS)
