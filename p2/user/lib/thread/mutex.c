#include <libthread.h>
#include <mutex_type.h>


extern int xchg();

int mutex_init(mutex_t *mp){

  mp->valid = 1;
  xchg(&mp->holder,-1);

  return 0; //Success
}

int mutex_destroy(mutex_t *mp){
  mp->valid = 0;
  free(mp);
  return 0;
}

int mutex_lock(mutex_t *mp){
  int tid = gettid();
  if(mp->holder == -1 && mp->valid){

    /* atomic swap*/
    xchg(&mp->holder,tid);

  }else if(mp->valid){

    /*attempt to yield to holder*/
    if(yield(mp->holder) < 0){
      printf("assert err mutex_lock0 %d\n",mp->holder);
      return -1; //If holder can't be called return an error
    } else {
      mutex_lock(mp); //Recusively call mutex_lock until lock can be aquired
    }

  }

  return 0;
}

int mutex_unlock(mutex_t *mp){

  int tid = gettid();
  if(tid == mp->holder){

    /* atomic swap*/
    xchg(&mp->holder,-1);

  }else if(mp->holder != -1){

    /*attempt to yield to holder*/
    if(yield(mp->holder) < 0){
      printf("assert err mutex_unlock0 %d\n",mp->holder);
      return -1;
    }else{
      mutex_unlock(mp);
    }

  }else{
    printf("assert err mutex_unlock1\n");
    return -1;
  }
  return 0;
}
