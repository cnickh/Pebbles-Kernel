/* libthread.h
*
* This file contian prototypes for all functions
* in the libthread.a static library, will possibly
* be broken up into multiple files in the future.
*
* Last Edit: 06/26/2020
* Written by: Charles Nick Henry
*/

#ifndef _LIBTHREAD_H_
#define _LIBTHREAD_H_

#include <cond_type.h>
#include <mutex_type.h>
#include <rwlock_type.h>
#include <sem_type.h>

#include <syscall.h> //for system calls
#include <stdio.h> //for printf(), could be removed
#include <stdlib.h> //malloc()

typedef struct stk_map { //Important variables for mapping the stack

  void *limit; //top of virtual process memory
  unsigned int tstack_sz; //space allocated for each thread


  mutex_t *lock;

} stk_map_t;

/* Defines a thread node to be used in tlist */
typedef struct thread_t {

  int tid, status;
  void *base; //%esp starting location

  struct thread_t *next;

}thread_t;

/*Functions for thread management*/
int thr_init(unsigned int size);

int thr_create(void *(*func)(void*), void *arg);

int thr_join(int tid, void **statusp);

void thr_exit (int status);

int thr_getid(void);

/*Functions for mutexes*/
int mutex_init(mutex_t *mp);

int mutex_destroy(mutex_t *mp);

int mutex_lock(mutex_t *mp);

int mutex_unlock(mutex_t *mp);

/*Functions for condition variables*/
int cond_init(cond_t *cv);

int cond_destroy(cond_t *cv);

int cond_wait(cond_t *cv, mutex_t *mp);

int cond_signal(cond_t *cv);

int cond_broadcast(cond_t *cv);

/*Functions for semaphores*/
int sem_init(sem_t *sem, int count);

int sem_destroy(sem_t *sem);

int sem_wait(sem_t *sem);

int sem_signal(sem_t *sem);

/*Functions for w/r blocking*/
int rwlock_int(rwlock_t *rwlock);

int rwlock_destroy(rwlock_t *rwlock);

int rwlock_lock(rwlock_t *rwlock, int type);

int rwlock_unlock(rwlock_t *rwlock);

#endif
