/* Test program for 15-412 project 3 Spring 2003
 * Zach Anderson(zra)
 *
 * testing robustness of kernel.
 * fork_bomb.c
 * A fork bomb.
 * Kernel should gracefully handle running out of
 * memory.
 */

/* Includes */
#include <syscall.h>    /* for fork */
#include <stdlib.h>     /* for exit */
#include <stdio.h>      /* for lprintf */
#include "410_tests.h"
static char test_name[]= "fork_bomb:";

/* Main */
int main()
{
	lprintf("%s%s%s",TEST_PFX,test_name,TEST_START_4EVER); 

	while( 1 ) fork();

	exit(42);
}
