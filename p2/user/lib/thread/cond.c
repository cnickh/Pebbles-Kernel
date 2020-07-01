#include <cond_type.h>
#include <mutex_type.h>

/*Functions for condition variables*/
int cond_init(cond_t *cv){
  return -1;
}

int cond_destroy(cond_t *cv){
  return -1;
}

int cond_wait(cond_t *cv, mutex_t *mp){
  return -1;
}

int cond_signal(cond_t *cv){
  return -1;
}

int cond_broadcast(cond_t *cv){
  return -1;
}
