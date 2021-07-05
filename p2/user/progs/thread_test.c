#include <stdlib.h>
#include <syscall.h>
#include <libthread.h>
#include <stdio.h>
#include <string.h>

#define stackSize 4096

#define SUCCESS 0



typedef struct myArgs{
	char cookie; /** each of my threads.... gets a cookie :) **/
} myArgs;

void *baseFunc (void* arg)
{
  printf("My sp 0x%x\n",get_sp());

  printf("My arg @ 0x%x\n",arg);

  printf("My arg = %d\n",*(unsigned int*)arg);

  //thr_exit(1);

	return (void*)69;

}

int main(int argc, char **argv)
{

  int *curArg = malloc(sizeof(int));

  *curArg = 69;

	thr_init(stackSize);


	int tid  = thr_create(baseFunc,curArg);

  void *statusp = malloc(sizeof(int));

  thr_join(tid,(void**)&statusp);

  printf("thread%d joined with status %d",tid,statusp);



	return 0;

}
