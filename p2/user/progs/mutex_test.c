#include <syscall.h>
#include <stdio.h>
#include <libthread.h>

#define STACK_SIZE 4096

#define STUPID_MAGIC_CONSTANT 4


int n_mutexes = 200; // number of mutexes in array - must be at least 1 and strictly larger than footprint
int n_chasethreads = 5; // total number of chase threads
int footprint = 2; // maximum number of mutexes held simultaneously by each thread - must be at least 2
int tid[20];
mutex_t * mtxs; // mutex array

void * chase(void * arg) {
  int next_mutex_to_acquire = 0;
  int highest_mutex_released = -1;
  // we don't want behavior to be determined by thread id policy, use 0..n_chasethreads-1 here (passed in as argument)
  int my_creation_number = (int)arg;

  printf("Starting chase thread with creation number %d\n", my_creation_number);

  while (highest_mutex_released < n_mutexes - 1) {

    // if we haven't acquired mutexes all the way to the end of the array, acquire one more
    if (next_mutex_to_acquire < n_mutexes) {
      mutex_lock(&(mtxs[next_mutex_to_acquire++]));
    }

    // TODO: here's the point that we 'periodically do something' such as sleep() or yield()
    if (((my_creation_number % STUPID_MAGIC_CONSTANT) == 0)
        && ((highest_mutex_released % STUPID_MAGIC_CONSTANT) == 0)) {
      yield(-1);
    }
    // we only start releasing mutexes when we've acquired a total of "footprint" mutexes
    if (next_mutex_to_acquire >= footprint) {
      mutex_unlock(&(mtxs[++highest_mutex_released]));
    }
  }

  printf("Successful finish for thread with creation number %d\n", my_creation_number);

  vanish();
  return (void *)1;
}


int main(){

  int i;
  void *statusp = malloc(sizeof(void*));
  int *arg = malloc(sizeof(int));
  mtxs = (mutex_t *)calloc(n_mutexes, sizeof(mutex_t));

  thr_init(STACK_SIZE);

  for (i = 0; i < n_mutexes; i++) {
      mutex_init(&(mtxs[i]));
  }
  for (i = 0; i < n_chasethreads; i++) {
      *arg = i;
      tid[i] = thr_create(chase,arg);
  }

  printf("entering the danger zone\n");

  for (i = 0; i < n_chasethreads; i++) {
      thr_join(tid[i],(void**)&statusp);
  }

  printf("past the danger zone\n");
  free(mtxs);
  free(arg);
    exit(0);

}
