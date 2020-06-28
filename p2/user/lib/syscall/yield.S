#include<syscall_int.h>

.global yield

yield:
  push %esi
  mov 8(%esp), %esi
  INT $YIELD_INT
  pop %esi
  ret
