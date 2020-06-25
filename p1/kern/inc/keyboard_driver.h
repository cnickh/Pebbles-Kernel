#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

#include <keyhelp.h>
#include <stdlib.h> //calloc()

#define KEY_BUF_SIZE 100

/*Define a struct to hold data from keyboard interrupts*/
typedef struct {
  char *buf;
  int size;
  int head;
  int tail;
} kbuf_t;

void init_kbuf();
/*allocates the necessary memory for the keyboard buffer*/

void add_to_kbuf(char);
/*adds the given byte to the keyboard buffer*/

int readchar();
/* returns the the next character in the keyboard buffer or
-1 if it contains no ascii value */


#endif
