#include <syscall_int.h>

.globl wait

wait:
  push %esi
  mov 8(%esp), %esi
  INT $WAIT_INT
  pop %esi
  ret
