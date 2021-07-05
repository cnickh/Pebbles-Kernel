#include <syscall_int.h>

.global thr_fork

thr_fork:

// Get the argument (nw %esp) and put it in %ebx
push %ebx
push %esi
push %edi
mov 16(%esp), %ebx
mov 20(%esp), %esi
mov 24(%esp), %edi

INT $THREAD_FORK_INT

// parent?
test %eax, %eax
jne .parent

// child
mov %ebx, %esp //Give the child a nw %esp
call *%esi


// return val?
test %eax, %eax
jne .set_status

//set defaul status
movl $0x9, (%edi)
INT $VANISH_INT

.set_status:
  mov %eax, (%edi)
  INT $VANISH_INT


.parent:
  pop %ebx
  pop %esi
  pop %edi
  ret

.globl get_bp

get_bp:
  mov %ebp, %eax
  ret

.globl get_sp

get_sp:
  mov %esp, %eax
  ret
