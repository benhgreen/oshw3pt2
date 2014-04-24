// very much incomplete, implemented basic thread/mutex functions, 
// scheduler is only prototyped

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <setjmp.h>
#include "myult.h"

int mypthread_create(myscheduler_t *scheduler, void *arg)
{
	mypthread_t *thread = malloc(sizeof(mypthread_t));
	thread->state = RUNNING;

	void *stack = calloc(STACK_SIZE, 0);

	ucontext_t context = calloc(sizeof(ucontext_t), 1);
	getcontext(context);
	context->uc_stack.ss_sp = stack;
	context->uc_stack.ss_size = STACK_SIZE;
	context->uc_link = scheduler->context;

	makecontext(context, thread, arg); //not sure about how to do this

	thread->scheduler = scheduler;
	scheduler->numthreads += 1;

	return thread;
}


void mypthread_exit(mypthread_t *thread)
{
	thread->state = FINISHED;
	thread->scheduler->finishedthreads += 1;
}

void mypthread_join(mypthread_t *local, mypthread_t *remote)
{
	local->state = JOINREADY;
	local->jointarget = remote;
	mypthread_yield(local);
	return;
}

void mypthread_yield(mypthread_t *thread)
{
	swapcontext(thread->context, thread->scheduler->context);
}

mymutex_t *mymutex_create()
{
	mymutex_t* newmutex = malloc(sizeof(mymutex_t));
	mymutex->state = UNLOCKED;
	mymutex->owner = NULL;
	return newmutex;
}	

void mymutex_lock(mypthread_t *thread, mymutex_t *mutex)
{
	if(mutex->state == LOCKED)
	{
		//block thread
		thread->blockcause = mutex;
		thread->state = BLOCKED
		thread->disabled = 1;
		
		//once unlocked
		if(mutex->state == UNLOCKED){
			mutex->state = LOCKED
			mutex->owner = thread;
		}
		
		thread->disabled = 0;


		return;
	}
}
int mymutex_trylock(mypthread_t *thread, mymutex_t *mutex)
{
	if(mutex->state == LOCKED){
		return 1;
	}else{
		mymutex_lock(thread, mutex);
		return 0;
	}

}
void mymutex_unlock(mypthread_t *thread, mymutex_t *mutex)
{
	if(mutex->state == UNLOCKED)
	{
		return;

	}else{

		if (mutex->owner == thread)
		{
			mutex->state = UNLOCKED;
			mutex->owner = NULL;
		}


	}

}