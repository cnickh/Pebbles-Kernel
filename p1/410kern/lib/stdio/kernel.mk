410KLIB_STDIO_OBJS := doprnt.o doscan.o printf.o putchar.o puts.o sprintf.o \
											sscanf.o
410KLIB_STDIO_OBJS := $(410KLIB_STDIO_OBJS:%=$(410KLIBDIR)/stdio/%)

ALL_410KOBJS += $(410KLIB_STDIO_OBJS)
410KCLEANS += $(410KLIBDIR)/libstdio.a

$(410KLIBDIR)/libstdio.a: $(410KLIB_STDIO_OBJS)
	$(AR) rc $@ $^
