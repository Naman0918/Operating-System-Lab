#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include “shm_com.h”

#define MAX 50

typedef struct sharedMem {
	int served;
	char msg[MAX];
}sharedMem;

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	int shmid;
	
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	shared_memory = shmat(shmid, (void *)0, 0);
	
	printf(“Memory attached at %d\n”, (int)shared_memory);

	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->written_by_you = 0;
	while(running) {
		if (shared_stuff->written_by_you) {
			printf(“You wrote: %s”, shared_stuff->some_text);
			sleep( rand() % 4 );
			shared_stuff->written_by_you = 0;
			if (strncmp(shared_stuff->some_text, “end”, 3) == 0) {
				running = 0;
			}
		}
	}

	exit(EXIT_SUCCESS);
}