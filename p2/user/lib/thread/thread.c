#include <libthread.h> //This file implements functions prototyped here
#include <syscall.h>
#include <stdio.h>


extern int thr_fork();

extern unsigned int get_bp();

extern unsigned int get_sp();

stk_map_t stk_map;

#define DECREMENT() (stk_map.limit - stk_map.tstack_sz)
#define MK_PAGE_ALIGN(size) (size - (size % PAGE_SIZE))


/*
* Simply set the stack space for each thread
*
*
*/
int thr_init(unsigned int size){
  stk_map.tstack_sz = MK_PAGE_ALIGN(size); //Set thread stack size
  stk_map.limit = (void *)(MK_PAGE_ALIGN(get_sp()) - 4*PAGE_SIZE);// - stk_map.tstack_sz); //Set top of stack memory to top of main's stack
  printf("tstack_sz = %08x, BP=%08x, SP=%08x\n",stk_map.tstack_sz,get_bp(),get_sp());
  return 0;
}


/*
*  Define stack space for the thread,
* call thr_fork() and pass (%esp) to the newly allocated stack space
*
*/
int thr_create(void *(*func)(void*), void *arg){

  int err;
  void **tbase = stk_map.limit-1;

  printf("Creating thread stack...\nbase @(%p), stk_size = %d\n",tbase,stk_map.tstack_sz);
  /*allocate space with new_pages()*/
  if((err = new_pages(stk_map.limit,stk_map.tstack_sz))>=0){

    /*IMPORTANT thread memory must be layed out BEFORE forking*/
    *tbase = func; 

    /*fork if we successed in making room*/
    if(!thr_fork(tbase,func)){

    }

    /*decrement task limit*/
    stk_map.limit = DECREMENT();

  } else {
    printf("MEM ERROR[%d]: Failed to create thread :( \n",err);
    return -1;
  }


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
