#include <libthread.h> //This file implements functions prototyped here
#include <syscall.h> //for system calls
#include <stdio.h> //for printf(), could be removed


extern int thr_fork();

extern unsigned int get_bp();

extern unsigned int get_sp();

stk_map_t stk_map;

llist_t *tlist;

#define DECREMENT() (stk_map.limit - stk_map.tstack_sz)

#define INCREMENT() (stk_map.limit + stk_map.tstack_sz)

#define MK_PAGE_ALIGN(size) (size - (size % PAGE_SIZE))


/*
* Simply set the stack size for each thread and initialize the stack limit and
* mutexes
*/
int thr_init(unsigned int size){

  /* Set thread stack size */
  stk_map.tstack_sz = MK_PAGE_ALIGN(size);

  /* Set limit of stack memory past bottom of autostack */
  stk_map.limit = (void *)(MK_PAGE_ALIGN(get_sp()) - 3*PAGE_SIZE);

  /* Initialize lock to protect stack*/
  mutex_init(&stk_map.lock);

  /*Initialize tlist*/
  thread_t main;
  main.tid = gettid();
  main.base = (void *)get_sp();
  main.status = NULL;
  tlist->tail = tlist->main = &main;
  tlist->main->next = NULL;

  return 0;
}


/*
*  Define stack base for the thread,
* call thr_fork() and pass %esp to the newly allocated stack space
*
_________STACK__________
0xfffff000, esp_main round down
0xffffe000, end of initial task stack
0xffffd000
0xffffc000, end of new mem  <----- initial stk_map.limit
0xffffb000, new_pages(PAGE_SIZE)

*/


int thr_create(void *(*func)(void*), void *arg){

  /* Make sure no other thread touches the stack at the same time*/
  mutex_lock(&stk_map.lock);

  /*Make an attempt to allocate memory*/
  int err = new_pages(DECREMENT(),stk_map.tstack_sz);

  /*Set the new thread stack base to the bottom of the current stack*/
  void *tbase = stk_map.limit-12;

  /*IMPORTANT thread memory must be layed out BEFORE forking*/
  *(unsigned int *)tbase = (unsigned int)func;
  *((unsigned int *)tbase +2) = (unsigned int)arg;

  /*fork and pass the thread esp*/
  int tid = thr_fork(tbase);

  /*decrement task limit, extend*/
  stk_map.limit = DECREMENT();

  mutex_unlock(&stk_map.lock);

  /*Add thread to tlist*/
  thread_t nw_thread;
  nw_thread.tid = tid;
  nw_thread.base = tbase;
  nw_thread.status = NULL;

  tlist->tail->next = &nw_thread;
  tlist->tail = &nw_thread;

  return 0;
}

/*
* This function needs to cause the calling thread to yield to the specified
* thread, and optionally place the exit_status of that thread in statusp.
*/

int thr_join(int tid, void **statusp){

  /* Find entry in tlist with tid */
  thread_t *temp = tlist->main;
  thread_t *prev, *next;

  while(temp != tlist->tail){
    next = temp-> next;
    if(tid == temp->tid) break;
    prev = temp;
    temp = temp->next;
  }

  //if not running
  if(temp->status != NULL){

      /* remove from tlist */
      prev->next = next;

      /* store status in statusp */
      *statusp = temp->status;

  }else{//else
      yield(tid);
      thr_join(tid,statusp);
    }


  return 0;
}

void thr_exit (void *status){

  void *sp = (void *)get_sp();
  thread_t *temp = tlist->main;
  thread_t *me = NULL;

  /* Find entry in tlist with sp */
  for (int i=0; i<PAGE_SIZE;i++){

    while(temp != tlist->tail){
      if(temp->base == sp +i){
        me = temp;
        break;
      }
      temp = temp->next;
    }
    if(me != NULL)break;
    temp = tlist->main;
  }

  /* Store status*/
  me->status = status;

  /* Free space*/
  remove_pages(me->base +12);

  vanish();
}

int thr_getid(void){
  return gettid();
}
