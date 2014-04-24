#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <setjmp.h>
#include "myult.h"

int mypthread_create(mypthread_t *thread, void *(*function), void *arg)
{

}


void mypthread_exit(void *returnvalue)
{

}

void mypthread_join(mypthread_t thread, void **returnvalue)
{

}

void mypthread_yield()
{

}

mymutex_t * mymutex_create()
{
	mymutex_t newmutex = create(mymutex_t);
	mymutex->state = UNLOCKED;
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
		if(mutex->state = UNLOCKED){
			mutex->state = LOCKED
			mutex->owner = thread;
		}
		
		thread->disabled = 0;


		return;
	}
}
void mymutex_()
{

}
void mymutex_()
{

}