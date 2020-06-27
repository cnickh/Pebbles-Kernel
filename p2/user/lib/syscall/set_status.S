#include <syscall_int.h>

.globl set_status

set_status:
  push %esi
  mov 8(%esp), %esi
  INT $SET_STATUS_INT
  pop %esi
  ret
