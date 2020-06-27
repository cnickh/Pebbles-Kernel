#include <libthread.h> //This file implements functions prototyped here


int thr_init(unsigned int size){
  return -1;
}

int thr_create(void *(*func)(void*), void *arg){
  return -1;
}

int thr_join(int tid, void **statusp){
  return -1;
}

void thr_exit (void *status){

}

int thr_getid(void){
  return -1;
}
