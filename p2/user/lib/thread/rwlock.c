/*Functions for w/r blocking*/
int rwlock_int(rwlock_t *rwlock);

int rwlock_destroy(rwlock_t *rwlock);

int rwlock_lock(rwlock_t *rwlock, int type);

int rwlock_unlock(rwlock_t *rwlock);
