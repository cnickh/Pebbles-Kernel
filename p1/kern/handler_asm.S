
.globl timer_handler_asm

.globl keyboard_handler_asm

timer_handler_asm:
  pusha
  call timer_handler
  popa
  iret

keyboard_handler_asm:
  pusha
  call keyboard_handler
  popa
  iret
