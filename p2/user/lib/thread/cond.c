#include <libthread.h>


/*Functions for condition variables*/
int cond_init(cond_t *cv){

  node_t head;
  head.tid = NULL;
  cv->qhead = cv->qtail = &head;
  cv->qhead->next = &cv->qtail;

  return 0;
}

/*@brief prevents threads from waiting for a dead or depreciated condition_var
*/
int cond_destroy(cond_t *cv){

  //Check wQueue and release waiting thread
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

  mutex_unlock(mp); //release lock

  //add to cv->wQueue
  node_t temp;
  temp.tid = gettid();
  cv->qtail->next = &temp;
  cv->qtail = &temp;

  //block with cas_runflag(gettid(),&0,&0,&-1);

  mutex_lock(mp); //aquire lock

  return 0;
}

/*@brief signals to wake up a waiting thread
* the first thread in the queue
*/
int cond_signal(cond_t *cv){

  //dequeue from wQueue
  //call cas_runflag()

  return -1;
}

/*@brief wakes up all thread currently waiting.
*/
int cond_broadcast(cond_t *cv){

  //loop and dequeue and call cas_runflag()

  return 0;
}
