// Libraries required for samphores
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>

// For printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* 
	 * Unnamed semaphor should be innitialized with `sem_init` and destroyed by
	 * `sem_destroy`
	 */
	sem_t	unnamed_sem;

	if (sem_init(&unnamed_sem, 1, 0))
	{
		printf("Failed to create unnamed semaphore.\n");
	}
	else
	{
		printf("Unnamed semaphore created.\n");
	}
	sem_destroy(&unnamed_sem);

	/* 
	 * Named semaphor should be opened with `sem_open` and closed by
	 * `sem_close`
	 */
	sem_t	*sem;
	sem = sem_open("fork1", O_CREAT, 0777, 0);
	if (sem == SEM_FAILED)
	{
		printf("Failed to create semaphore.\n");
		return (1);
	}
	else
	{
		printf("Semaphore created at %p\n", sem);
	}
	/* sem_close(sem);
	sem = NULL; */


	pid_t	id;

	id = 1;
	for (int i = 0; i < 5; i++)
	{
		if (id != 0) id = fork();
	}
	if (id == 0)
	{
		printf("%d Waiting on semaphore.\n", getpid());
		sem_wait(sem); // Basically decrements the sem by 1
		printf("%d Received semaphore.\n", getpid());
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			sleep(1);
			printf("%d Posting semaphore.\n", getpid());
			/* 
			 * Each time a semaphore is posted, only one thread/process waiting
			 * on the semaphore can receive it. Basically increments the sem by
			 * 1.
			 */
			sem_post(sem);
		}
	}
	/*
	 * Memory space is cloned during fork, so each child process needs to free
	 * all the allocated memory.
	 */
	sem_close(sem);
	return 0;
}
