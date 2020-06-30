#include <syscall_int.h>


.globl new_pages

new_pages:
  push %esi
  lea 8(%esp), %esi
  INT $NEW_PAGES_INT
  pop %esi
  ret
