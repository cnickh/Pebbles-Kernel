/* The 15-410 kernel.
 * syscall.h
 *
 * Prototypes for the user land C library interface
 * to system calls.
 *
 */

#ifndef _SYSCALL_H
#define _SYSCALL_H

#define NORETURN __attribute__((__noreturn__))

#define PAGE_SIZE 0x0001000 /* 4096 */

/* Life cycle */
int fork(void);
int exec(char *execname, char *argvec[]);
void set_status(int status);
void vanish(void) NORETURN;
int wait(int *status_ptr);
void task_vanish(int status) NORETURN;

/* Thread management */
int gettid(void);
int yield(int pid);
int cas_runflag(int tid, int *oldp, int *expectp, int *newp);
int get_ticks();
int sleep(int ticks);

/* Memory management */
int new_pages(void * addr, int len);
int remove_pages(void * addr);

/* Console I/O */
char getchar(void);
int readline(int size, char *buf);
int print(int size, char *buf);
int set_term_color(int color);
int set_cursor_pos(int row, int col);
int get_cursor_pos(int *row, int *col);

/* Miscellaneous */
void halt();
int ls(int size, char *buf);

/* "Special" */
void misbehave(int mode);

/* Previous API */
/*
void exit(int status) NORETURN;
void task_exit(int status) NORETURN;
int deschedule(int *flag);
int make_runnable(int pid);
*/

#endif /* _SYSCALL_H */
