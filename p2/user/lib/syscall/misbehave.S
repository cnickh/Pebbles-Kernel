#include<syscall_int.h>

.globl misbehave

misbehave:
  push %esi
  mov 8(%esp), %esi
  INT $MISBEHAVE_INT
  pop %esi
  ret
