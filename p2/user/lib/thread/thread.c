#include <libthread.h> //This file implements functions prototyped here



extern int thr_fork();

extern unsigned int get_bp();

extern unsigned int get_sp();

stk_map_t *stk_map;

llist_t *tlist;

#define DECREMENT() (stk_map->limit - stk_map->tstack_sz)

#define INCREMENT() (stk_map->limit + stk_map->tstack_sz)

#define MK_PAGE_ALIGN(size) (size - (size % PAGE_SIZE))


/*
* Simply set the stack size for each thread and initialize the stack limit and
* mutexes
*/
int thr_init(unsigned int size){

  /* malloc space for the thread list here after "tlist"*/
  tlist = malloc(sizeof(llist_t));
  stk_map = malloc(sizeof(stk_map));


  /* Set thread stack size */
  stk_map->tstack_sz = MK_PAGE_ALIGN(size);

  /* Set limit of stack memory past bottom of autostack */
  stk_map->limit = (void *)(MK_PAGE_ALIGN(get_sp()) - 3*PAGE_SIZE);

  /* Initialize lock to protect stack*/
  mutex_init(&stk_map->lock);

  /*Initialize tlist*/
  thread_t *main = malloc(sizeof(thread_t));
  main->tid = gettid();
  main->base = (void *)get_sp();
  main->status = NULL;
  tlist->tail = tlist->main = main;
  tlist->main->next = NULL;

  return 0;
}


/*
*  Define stack base for the thread,
* call thr_fork() and pass %esp to the newly allocated stack space
*
_________STACK__________
0xfffff000, lowest address of main thread' stack
0xffffe000, end of initial  autostack
0xffffd000, initial value of stk_map.limit
0xffffc000
0xffffb000, 1st new_pages(PAGE_SIZE) call

*/


int thr_create(void *(*func)(void*), void *arg){

  /*create object to track thread*/
  thread_t *nw_thread = malloc(sizeof(thread_t));

  /* Make sure no other thread touches the stack at the same time*/
  mutex_lock(&stk_map->lock);

  /*Set the new thread stack base to the bottom of the current stack*/
  void *thr_sp = stk_map->limit-16;

  /*decrement task limit, extend*/
  stk_map->limit = DECREMENT();

  /*Make an attempt to allocate memory*/
  int err = new_pages(stk_map->limit,stk_map->tstack_sz);
  if(err != 0){
    printf("new_pages failed with %d\n",err);
  }else{
    nw_thread->base = stk_map->limit;
  }

  mutex_unlock(&stk_map->lock);

  /*IMPORTANT thread memory must be layed out BEFORE forking*/
  *((unsigned int *)thr_sp) = (unsigned int)arg;
  *((unsigned int *)thr_sp+2) = (unsigned int)func;
  *((unsigned int *)thr_sp+3) = (unsigned int)&nw_thread->status;


  /*fork and pass the thread esp*/
  int tid = thr_fork(thr_sp);

  /*Add thread to tlist*/
  nw_thread->tid = tid;
  nw_thread->status = NULL;

  tlist->tail->next = nw_thread;
  tlist->tail = nw_thread;

  return tid;
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
    next = temp->next;
    if(tid == temp->tid)break;
    prev = temp;
    temp = temp->next;
  }

  if(temp->tid != tid){
    return -1;
  }

  //if not running
  if(temp->status != NULL){

      /* remove from tlist */
      prev->next = next;

      /* store status in statusp */
      *statusp = (void *)temp->status;

      /*free space*/
      remove_pages(temp->base);
      free(temp);


  }else{//else
    yield(tid);
    thr_join(tid,statusp);
  }

  return 0;
}

void thr_exit (int status){

  thread_t *temp = tlist->main;

  int tid = gettid();

  /* Find entry in tlist with tid */
  while(temp != tlist->tail){
    if(temp->tid == tid)break;
    temp = temp->next;
  }

  /* Store status*/
  temp->status = status;

  vanish();
}

int thr_getid(void){
  return gettid();
}
