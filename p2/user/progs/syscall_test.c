#include <syscall.h>
#include <stdio.h>

int main(){

  int exit_status; //create a pointer to store forked processes exit status
  char *args[1];
  args[0] = "forkedp\0";
  int pid = fork();

  if(!pid)//fork a new process
    exec("forkedp",args);

  printf("now waiting for forkedp...\n");
  pid = wait(&exit_status);

  set_status(84); //set exit status of this process

  //int pid = wait(exit_status); //get exit status of forked process
  printf("p(%d) exit status: %d\n", pid, exit_status); //print exit status of forked process

  vanish(); //kill process
}
