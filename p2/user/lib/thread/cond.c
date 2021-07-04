#include <libthread.h>


/*Functions for condition variables*/
int cond_init(cond_t *cv){

  node_t *head = malloc(sizeof(node_t));
  head->tid = NULL;
  cv->qhead = cv->qtail = head;
  cv->qhead->next = NULL;

  return 0;
}

/*@brief prevents threads from waiting for a dead or depreciated condition_var
*/
int cond_destroy(cond_t *cv){

  node_t *temp = cv->qhead;

  int *newp = malloc(sizeof(int));
  int *expectp = malloc(sizeof(int));

  //Check wQueue and release waiting thread
  while(temp != cv->qtail){

    if(temp->tid != NULL)
      printf("cas_ runflag() %d",cas_runflag(temp->tid,temp->oldflag,expectp,newp));

    temp = temp->next;
  }


  free(newp);
  free(expectp);
  //set invalid


  return 0;
}

/*@brief calling thread waits/suspends execution
* until a call to signal() on the refrenced cv is made.
* the mutex @mp should be released. If it is aquired before the
* calling thread has blocked, and signal() is called the thread may resume
* without blocking
*/
int cond_wait(cond_t *cv, mutex_t *mp){

  int tid = gettid();

  node_t *temp = malloc(sizeof(node_t));

  temp->oldflag = malloc(sizeof(int));

  int *expectp = malloc(sizeof(int));

  int *newp = malloc(sizeof(int));

  mutex_unlock(mp); //release lock

  temp->tid = tid;

  /*add to cv->wQueue*/
  if(cv->qhead->tid == NULL){
    cv->qhead = cv->qtail = temp;
  }else{
    cv->qtail->next = temp;
    cv->qtail = temp;
  }

  /*set up for cas_runflag call*/
  *temp->oldflag = 0;
  *expectp = 0;
  *newp = -1;

  //block with cas_runflag(int tid, int *oldp, int *expectp, int *newp);
  printf("cas_ runflag() %d",cas_runflag(tid,temp->oldflag,expectp,newp));

  free(newp);
  free(expectp);

  mutex_lock(mp); //aquire lock

  return 0;
}

/*@brief signals to wake up a waiting thread
* the first thread in the queue
*/
int cond_signal(cond_t *cv){

  node_t *temp;

  int *expectp = malloc(sizeof(int));

  int *newp = malloc(sizeof(int));

  /*dequeue from wQueue*/
  temp = cv->qhead;
  cv->qhead = temp->next;

  *expectp = -1;
  *newp = 0;

  /*call cas_runflag()*/
  if(temp->tid != NULL){
    printf("cas_ runflag() %d",cas_runflag(temp->tid,temp->oldflag,expectp,newp));

    free(expectp);
    free(newp);
    free(temp->oldflag);
    free(temp);

    return 0;
  }else{
    return -1;
  }
}

/*@brief wakes up all threads currently waiting.
*/
int cond_broadcast(cond_t *cv){

  //loop and dequeue and call cas_runflag()

  return 0;
}
