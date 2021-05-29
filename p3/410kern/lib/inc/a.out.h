#ifndef _A_OUT_H
#define	_A_OUT_H 1

/* --- The a.out header struct --- */
typedef struct exec {
  unsigned long   a_midmag; /* The magic number */
  unsigned long   a_text;   /* length of text section */
  unsigned long   a_data;   /* length of data section */
  unsigned long   a_bss;    /* length of bss  section */
  unsigned long   a_syms;   /* length of symbol table in bytes */
  unsigned long   a_entry;  /* entry point */
  unsigned long   a_trsize; /* length of relocation info for text */
  unsigned long   a_drsize; /* length of relocation info for data */
} exec_t;

#ifndef CODE_BEGIN
#define CODE_BEGIN (char*)0x1000000
#endif

/*
 * Helpers for loading a.out binaries.
 */
int a_out_load_helper( simple_elf_t *se_hdr, const char *fname );
int a_out_check_header( const char *fname );

#endif
