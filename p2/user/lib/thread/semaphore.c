
/*Functions for semaphores*/
int sem_init(sem_t *sem, int count);

int sem_destroy(sem_t *sem);

int sem_wait(sem_t *sem);

int sem_signal(sem_t *sem);
