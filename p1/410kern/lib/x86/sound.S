/**
 * The 15-410 Reference Kernel
 * @name sound.h
 *
 * Function for using the PC Speaker.
 *
 * @author Zachary Anderson(zra)
 */

.globl spkr_on
spkr_on:
	push	%ebp
	movl	%esp, %ebp

	movl	0x8(%ebp), %ebx	# pitch

	mov	$0xb6, %al
	out	%al, $0x43
	mov	%ebx, %eax

	out	%al, $0x42
	mov	%ah, %al
	out	%al, $0x42
	in	$0x61, %al

	or	$0x3, %al
	out	%al, $0x61

	movl	%ebp, %esp
	pop	%ebp
	ret

.globl spkr_off
spkr_off:
	push	%ebp
	movl	%esp, %ebp

	in	$0x61, %al
	and	$0xfc, %al
	out	%al, $0x61

	movl	%ebp, %esp
	pop	%ebp
	ret
