#ifndef MYULT
#define MYULT

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>


#define STACK_SIZE 1024*128

typedef struct myscheduler
{
	struct mynode *queue;
	ucontext_t *context;
	mypthread_t current;
	int disabled;

	int numthreads;
	int finishedthreads;

} myscheduler_t;

typedef struct mypthread
{
	struct mypthread *jointarget;
	ucontext_t context;
	myscheduler_t scheduler;
	typedef enum {READY, WAITING, KILLED, BLOCKED, JOINREADY, FINISHED} state;
	
} mypthread_t;

typedef struct mymutex
{
	enum {LOCKED, UNLOCKED} state;
	mypthread_t *owner
} mymutex_t;


int mypthread_create(myscheduler_t *scheduler, void *arg);
void mypthread_yield(mypthread_t *local, *mypthread_t remote);
void mypthread_join(mypthread_t *local, mypthread_t *remote);
void mypthread_exit(mypthread_t *thread);


mymutex_t* mymutex_create();
void mymutex_lock(mypthread_t *thread, mymutex_t *mutex);
void mymutex_unlock(mypthread_t *thread, mymutex_t *mutex);
int mymutex_trylock(mypthread_t *thread, mymutex_t *mutex);



#endif