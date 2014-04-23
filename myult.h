#ifndef MYULT
#define MYULT

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>


#define STACK_SIZE 1024*128

typedef struct mypthread
{
	typedef enum {READY, WAITING, KILLED, BLOCKED} state;
} mypthread_t;

typedef struct mymutex
{
	enum {LOCKED, UNLOCKED} state;
	mypthread_t *owner
} mymutex_t;






#endif