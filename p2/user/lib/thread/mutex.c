#include <mutex_type.h>
#include <syscall.h>


int mutex_init(mutex_t *mp){
  mp->valid = 1;
  mp->lock = 1;

  mp->holder = -1;

  return 0; //Success
}

int mutex_destroy(mutex_t *mp){
  mp->valid = 0;
  return 0;
}

int mutex_lock(mutex_t *mp){

  if(mp->lock && mp->valid){ //If available grab and set yourself as holder
    mp->lock = 0;
    mp->holder = gettid();
    return 1;
  } else if(mp->valid){ //If locked yield to the holder

    if(yield(mp->holder) < 0){
      return -1; //If holder can't be called return an error
    } else {
      mutex_lock(mp); //Recusively call mutex_lock until lock can be aquired
    }

  } else {
    return -2; //return error on invalid lock
  }
}

int mutex_unlock(mutex_t *mp){
  mp->lock = 1; //Make lock available
  mp->holder = -1; //Clear holder
  return 0;
}
