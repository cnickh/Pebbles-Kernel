/*Functions for condition variables*/
int cond_init(cond_t *cv);

int cond_destroy(cond_t *cv);

int cond_wait(cond_t *cv, mutex_t *mp);

int cond_signal(cond_t *cv);

int cond_broadcast(cond_t *cv);
