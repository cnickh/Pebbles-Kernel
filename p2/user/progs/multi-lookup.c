/* @brief This file contains the code for the multi-lookup program. This program
* is based off the CU-3753 multi-lookup homework assignment. It's purpose is
* to test the functionality of mutexes and thread creation by the libthread library
*
* author: Charles Henry
* created: 07/02/20
*/
#include <libthead.h>

#define NUM_REQ 5
#define NUM_RES 5
#define MAX_LEN 2048
#define MAX_ITEMS 10

typedef struct thread_data_t{

  /*Data to service*/
  char sharedBuffer[MAX_ITEMS][MAX_LEN];
  char toService[MAX_ITEMS][MAX_LEN];
  char serviced[MAX_ITEMS][MAX_LEN];

  /*Pointers*/
  short bufPointer;
  short toServ;
  short served;

} thread_data_t

/* Code to populate sharedBuffer and requester work */
void *requester(void *arg){

  thread_data_t *data = (thread_data_t*)arg;

  while()

  vanish();
}

/* Code to take from sharedBuffer and perform work */
void *resolver(void *arg){

  thread_data_t *data = (thread_data_t*)arg;

  vanish();
}


void print_results(char serviced[MAX_ITEMS][MAX_LEN]){
  for (int i=0;i<MAX_ITEMS;i++){
    printf("%s\n"serviced[i]);
  }
}

int main(){

  /* Declare and allocate space for shared data */
  thread_data_t *data = malloc(sizeof(thread_data_t));

  /* populate shared data  with items to service */


  for(int i; i < NUM_REQ; i++)
    thr_create(requester,data);
  for(int i; i < NUM_RES; i++)
    thr_create(resolver,data);
}
