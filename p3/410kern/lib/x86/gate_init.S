/** @brief Gate initialization function
 *
 *  Optimized version of OSKit code
 *
 *  Changes made by Zachary Anderson (zra)
 *  @author Mark T. Tomczak
 **/

.globl gate_init        
gate_init:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	nop
.L2:
	movl	12(%ebp), %eax
	cmpl	$0, (%eax)
	jne	.L4
	jmp	.L1
.L4:
	movl	12(%ebp), %eax
	movzwl	4(%eax), %eax
	sall	$3, %eax
	addl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	movzwl	(%eax), %eax
	movw	%ax, (%edx)
	movl	-4(%ebp), %edx
	movl	16(%ebp), %eax
	movw	%ax, 2(%edx)
	movl	-4(%ebp), %eax
	movb	$0, 4(%eax)
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	movzbl	6(%eax), %eax
	orb	$-128, %al
	movb	%al, 5(%edx)
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	shrl	$16, %eax
	movw	%ax, 6(%edx)
	leal	12(%ebp), %eax
	addl	$8, (%eax)
	jmp	.L2
.L1:
	leave
	ret
