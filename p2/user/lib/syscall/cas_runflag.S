#include <syscall_int.h>

.globl cas_runflag

cas_runflag:
  push %esi
  lea 8(%esp), %esi
  INT $CAS_RUNFLAG_INT
  pop %esi
  ret
