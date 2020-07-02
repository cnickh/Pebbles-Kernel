#include<syscall.h>
#include<stdio.h>

int main(int argc, char *argv[]){

  set_status(69);
  printf("Hello from forkedp\n");
  vanish();

}
