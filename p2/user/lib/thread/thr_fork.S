#include <syscall_int.h>

.global thr_fork

thr_fork:

// Get the argument (nw %esp) and put it in %ebx
push %ebx
mov 8(%esp), %ebx

INT $THREAD_FORK_INT

// parent?
test %eax, %eax
jne .parent

// child
mov %ebx, %esp //Give the child a nw %esp
call 8(%esp)
mov 12(%esp), %edx
// return val?
test %eax, %eax
jne .set_status

//set defaul status
mov $0x1, %ebx
mov %ebx, (%edx)
INT $VANISH_INT

.set_status:
  mov %eax, (%edx)
  INT $VANISH_INT


.parent:
  pop %ebx
  ret

.globl get_bp

get_bp:
  mov %ebp, %eax
  ret

.globl get_sp

get_sp:
  mov %esp, %eax
  ret
