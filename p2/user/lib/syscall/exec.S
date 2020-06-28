#include <syscall_int.h>

.globl exec

exec:
  push %esi
  lea 8(%esp), %esi
  INT $EXEC_INT
  pop %esi
  ret
