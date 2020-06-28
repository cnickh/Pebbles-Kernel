#include<syscall_int.h>

.globl print

print:
  push %esi
  lea 8(%esp),%esi
  INT $PRINT_INT
  pop %esi
  ret
