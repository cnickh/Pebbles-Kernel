/** @file tick.c
 *  @brief Tick function, to be called by the timer interrupt handler
 *
 *  Fill in this tick function with any processing your game needs
 *  to do on each timer interrupt. This function should be called from your
 *  timer interrupt handler, even if it is empty.
 *
 *  Function declared in 410_reqs.h
 *
 *  @author Charles Nick Henry
 *  @bug None known
 **/

#include <410_reqs.h>
#include <keyboard_driver.h>
#include <console.h>

void tick(unsigned int numTicks)
{
  char ch;
  if((ch = readchar()) != -1)putbyte(ch);
}
