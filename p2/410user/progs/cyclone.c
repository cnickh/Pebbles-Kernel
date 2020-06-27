/**
 * @file cyclone.c
 * @brief A test of basic thread behaviors with misbehavior
 *
 * This test spawns a thread and then attempts to join it
 * with each misbehavior mode.
 *
 * @author Michael Berman (mberman)
 * @author Based on thr_join0_test by Joey Echeverria (jge)
 * @bug No known bugs.
 */

#include <thread.h>
#include <syscall.h>
#include <stdio.h>

#define STACK_SIZE 4096
#define MAX_MISBEHAVE 32

int thread_exited = 0;
int thr_exit_return = 0;

void* thread1(void* token);

/**
 * @brief Spawns the thread and attempts to join
 *
 * @param argc The number of arguments
 * @param argv The argument array
 * @return 1 on success, < 0 on error.
 */
int main(int argc, char *argv[])
{
	int status;
	int i;
  int spawn_tid;

	thr_init(STACK_SIZE);

	for (i = 0; i < MAX_MISBEHAVE; i++) {
	  thread_exited = 0;
	  thr_exit_return = 0;

	  misbehave(i);

	  spawn_tid = thr_create(thread1, (void*)i);

	  thr_join(spawn_tid, (void**)&status);

	  if(thread_exited == 0) {
	    return -40;
	  }

	  if(status != i) {
	    return -60;
	  }
	  
	  if(thr_exit_return) {
	    return -70;
	  }
	}


	return 1;
}

/**
 * @brief Simply exit
 *
 * @param token An integer token to pass to thr_exit
 * @return The passed in token.
 */
void* thread1(void* token)
{
	thread_exited = 1;
	thr_exit(token);
	thr_exit_return = 1;

	return token;
}
