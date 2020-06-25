/*
 * As you can see, you can perform c style comments in .S files.
 * You may also use precompiler directives like #include and #define
 */


/* define the add_one1 and add_one2 labels so that they can be called from
 other files (.c or .S) */

.global get_bp
.type get_caller, @function

/* Method 1 saves off all of the callee save registers
 * and then adds one to the argument and returns it
 */

get_bp:
	movl	%ebp, %eax	# get the return address
	ret
