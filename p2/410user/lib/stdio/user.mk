410ULIB_STDIO_OBJS := doprnt.o doscan.o printf.o putchar.o puts.o sprintf.o \
                     sscanf.o
410ULIB_STDIO_OBJS := $(410ULIB_STDIO_OBJS:%=$(410ULIBDIR)/stdio/%)

ALL_410UOBJS += $(410ULIB_STDIO_OBJS)
410UCLEANS += $(410ULIBDIR)/libstdio.a

$(410ULIBDIR)/libstdio.a: $(410ULIB_STDIO_OBJS)
