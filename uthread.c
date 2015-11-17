#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

/*
 * This is where you'll need to implement the user-level functions
 */

void *tstacks[64]; // max amount of proc available CK

void lock_init(lock_t *lock) {
	//lock = malloc(sizeof(lock_t));
	//initlock(lock->spinny, "spinny");
	lock->value = 0;
}

void lock_acquire(lock_t *lock) {
	while (xchg(&lock->value, 1) != 0) {}
}

void lock_release(lock_t *lock) {
	xchg(&lock->value, 0);
}

int thread_join(int pid) {
	int pnum;
	if ((pnum = join(pid)) != -1) {// have to separate pid and pnum in case of -1 CK
		free(tstacks[pnum]);
	} 
	//printf(1, "Pid in join: %d\n", pnum);
	return pnum;
}

int thread_create(void (*start_routine)(void *), void *arg) {
	int pid;
	int PGSIZE = 4096;
	// base gotten from clonetest1 CK
	void *stack = malloc(PGSIZE*2);

  	if((uint)stack % PGSIZE)
     	stack = stack + (PGSIZE - (uint)stack % PGSIZE);
	
	
	if ((pid = clone(start_routine, arg, stack)) < 0) {
		return -1;
	}
	
	tstacks[pid] = stack; // so it is accessable later
	
	return pid;
	
}
