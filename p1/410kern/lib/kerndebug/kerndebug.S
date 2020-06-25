/* The 15-410 kernel project.
 * kerndebug.S
 *
 * Functions related to using Simics for
 * debugging the kernel and user processes.
 * 
 * Don't be tempted to move the functions
 * for disabling and enabling interrupts here.
 * They need to stay #defined so that we know
 * where in the kernel it happened.
 *
 * Zachary Anderson (zra)
 */

.global SIM_register_user_proc
SIM_register_user_proc:
	push	%ebp
	mov	%esp, %ebp

	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	mov	0x8(%ebp), %eax /* the cr3 */
	mov	0xc(%ebp), %ecx /* file name */
	mov	$0x5badd00d , %ebx
	xchg	%bx, %bx
	popl	%ecx
	popl	%ebx
	popl	%eax

	mov	%ebp, %esp
	pop	%ebp
	ret

.global SIM_register_user_from_parent
SIM_register_user_from_parent:
	push    %ebp
	mov     %esp, %ebp

	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	mov     0x8(%ebp), %eax /* the child cr3 */
	mov	0xc(%ebp), %ecx /* the parent cr3 */
	mov     $0x8badd00d , %ebx
	xchg    %bx, %bx
	popl	%ecx
	popl	%ebx
	popl	%eax

	mov     %ebp, %esp
	pop     %ebp
	ret

.globl SIM_unregister_user_proc
SIM_unregister_user_proc:
	push	%ebp
	mov	%esp, %ebp

	pushl	%eax
	pushl	%ebx
	mov	0x8(%ebp), %eax /* the cr3 */
	mov	$0x6badd00d, %ebx
	xchg	%bx, %bx
	popl	%ebx
	popl	%eax

	mov	%ebp, %esp
	pop	%ebp
	ret

.globl SIM_halt
SIM_halt:
	movl	$0xdeadd00d, %ebx
	xchg	%bx, %bx

.globl SIM_beep
SIM_beep:
	push	%ebp
	mov	%esp, %ebp

	pushl	%ebx
	movl	$0x9badd00d, %ebx
	xchg	%bx, %bx
	popl	%ebx

	movl	%ebp, %esp
	pop	%ebp
	ret

.globl SIM_switch
SIM_switch:
	push	%ebp
	mov	%esp, %ebp

	pushl	%eax
	pushl	%ebx
	movl	0x8(%ebp), %eax
	movl	$0x7badd00d, %ebx
	xchg	%bx, %bx
	popl	%ebx
	popl	%eax

	mov	%ebp, %esp
	pop	%ebp
	ret
