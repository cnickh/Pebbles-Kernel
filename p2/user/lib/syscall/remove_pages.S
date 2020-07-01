#include <syscall_int.h>


.globl remove_pages

remove_pages:
  push %esi
  mov 8(%esp), %esi
  INT $REMOVE_PAGES_INT
  pop %esi
  ret
