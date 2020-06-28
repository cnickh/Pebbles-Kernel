#include<syscall.h>
#include<stdio.h>

int main(){
  set_status(69);
  printf("Hello from forkedp\n");
  vanish();
}
