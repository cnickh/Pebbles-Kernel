#include <libthread.h> //This file implements functions prototyped here
#include <syscall.h> //for system calls
#include <stdio.h> //for printf(), could be removed
#include <string.h> //for memset()
#include <stdlib.h>//for malloc()?


extern int thr_fork();

extern unsigned int get_bp();

extern unsigned int get_sp();

stk_map_t stk_map;

#define DECREMENT() (stk_map.limit - stk_map.tstack_sz)

#define INCREMENT() (stk_map.limit + stk_map.tstack_sz)

#define MK_PAGE_ALIGN(size) (size - (size % PAGE_SIZE))


/*
* Simply set the stack space for each thread
*
*/
int thr_init(unsigned int size){

  /* Set thread stack size */
  stk_map.tstack_sz = MK_PAGE_ALIGN(size);

  /* Set top of stack memory to top of main's stack */
  stk_map.limit = (void *)(MK_PAGE_ALIGN(get_sp()));

  return 0;
}


/*
*  Define stack base for the thread,
* call thr_fork() and pass %esp to the newly allocated stack space
*
*/
int thr_create(void *(*func)(void*), void *arg){

  void *tbase = stk_map.limit;

  /*IMPORTANT thread memory must be layed out BEFORE forking*/
  *(unsigned int *)tbase = (unsigned int)func;
  *((unsigned int *)tbase +2) = (unsigned int)arg;

  /*fork and pass the thread esp*/
  thr_fork(tbase);
  printf("thread has been made @%p\n",tbase);


  /*decrement task limit*/
  stk_map.limit = DECREMENT();
  //int err = new_pages(stk_map.limit,stk_map.tstack_sz); //allocate space if needed
//  printf("new_pages return [%d]\n",err);
  return 0;
}

int thr_join(int tid, void **statusp){
  return -1;
}

void thr_exit (void *status){

}

int thr_getid(void){
  return -1;
}
