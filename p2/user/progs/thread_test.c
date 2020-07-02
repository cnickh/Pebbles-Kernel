#include <syscall.h>
#include <stdio.h>
#include <libthread.h>
#include <stdlib.h>


void *thread0(void*ptr){
  printf("Hello from thread%d\n",thr_getid());
  vanish();
}

void *thread1(void*ptr){
  printf("Hello from thread%d\n",thr_getid());
  vanish();
}

void *thread2(void*ptr){
  printf("Hello from thread%d\n",thr_getid());
  vanish();
}

int main(){


  thr_init(4096);

  void *ptr = _malloc(sizeof(int));
  thr_create(thread0,ptr);
  thr_create(thread1,ptr);
  thr_create(thread2,ptr);

  printf("hello from main \n");
  vanish();

}
