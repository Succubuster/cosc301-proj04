#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

/*
 * This is where you'll need to implement the user-level functions
 */


void lock_init(lock_t *lock) {
	lock = malloc(sizeof(lock_t));
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
	return join(pid);
}

int thread_create(void (*start_routine)(void *), void *arg) {
	int pid;
	void* stck = malloc(4096); // should be PGSIZE CK 
	if ((pid = clone(start_routine, arg, (char*)stck + 4096)) < 0) {
		return -1;
	}
	return pid;
	
}
