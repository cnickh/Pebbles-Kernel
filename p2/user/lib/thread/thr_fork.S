#include <syscall_int.h>

.global thr_fork

thr_fork:

// Get the argument (nw %ebp) and put it in %ebx
push %ebx
mov 8(%esp), %ebx

INT $THREAD_FORK_INT

// parent?
test %eax, %eax
jne .parent

// child!
mov %ebx, %ebp //Give the child a nw %ebp
mov %ebp, %esp //Give the child a nw %esp
ret

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
