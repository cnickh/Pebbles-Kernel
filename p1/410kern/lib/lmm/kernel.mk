410KLIB_LMM_OBJS := lmm_add_free.o lmm_add_region.o lmm_alloc.o                \
                    lmm_alloc_aligned.o lmm_alloc_gen.o lmm_alloc_page.o       \
                    lmm_avail.o lmm_avail_in.o lmm_dump.o lmm_find_free.o      \
                    lmm_free.o lmm_free_page.o lmm_init.o lmm_remove_free.o    \
                    lmm_stats.o phys_lmm_add.o phys_lmm_init.o phys_mem_max.o  \
                    phys_mem_min.o phys_mem_va.o linear_base_va.o lmm.malloc.o \
                    malloc.o mallocf.o smalloc.o smallocf.o
#Append directory prefix
410KLIB_LMM_OBJS := $(patsubst %,$(410KLIBDIR)/lmm/%,$(410KLIB_LMM_OBJS))

ALL_410KOBJS += $(410KLIB_LMM_OBJS)
410KCLEANS += $(410KLIBDIR)/liblmm.a

$(410KLIBDIR)/liblmm.a: $(410KLIB_LMM_OBJS)
