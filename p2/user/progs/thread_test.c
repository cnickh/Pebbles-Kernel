#include <syscall.h>
#include <stdio.h>
#include <libthread.h>

void thread(){
  printf("Hello from my first thread\n");
}

int main(){
  void *ptr;
  thr_init(4096);
  thr_create(thread,ptr);
  printf("hello from main\n");
}
