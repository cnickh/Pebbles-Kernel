410KLIB_RTC_OBJS:= rtc.o 
410KLIB_RTC_OBJS:= $(410KLIB_RTC_OBJS:%=$(410KLIBDIR)/rtc/%)

ALL_410KOBJS += $(410KLIB_RTC_OBJS)
410KCLEANS += $(410KLIBDIR)/librtc.a

$(410KLIBDIR)/librtc.a: $(410KLIB_RTC_OBJS)
	$(AR) rc $@ $^
