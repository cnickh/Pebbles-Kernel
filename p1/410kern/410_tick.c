/** @file tick.c
 *  @brief Tick function, to be called by the timer interrupt handler
 * 
 *  Tick function used by 410_test.c 
 *  
 *  Function declared in 410_reqs.h
 *
 *  @author Claire Tokar (ctokar)
 *  @bug None known
 **/

#include <410_reqs.h>
#include <console.h>
#include <stdio.h>

static unsigned int totalTime = 0;

void tick(unsigned int numTicks)
{
	if (numTicks % 100 == 0) {
		totalTime++;
		set_cursor((CONSOLE_HEIGHT/2)+1,(CONSOLE_WIDTH/2)-3);
		printf("%.2d:%.2d", totalTime/60, totalTime%60);
	}
}
