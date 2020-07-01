#include <syscall_int.h>

.globl gettid

gettid:
  INT $GETTID_INT
  ret
