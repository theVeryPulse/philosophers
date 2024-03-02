#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int data = 0;

void *resource1(void *ptr)
{
    // pthread_mutex_lock blocks until the mutex lock is secured.
   /*  if (pthread_mutex_lock((pthread_mutex_t *)ptr) == 0)
        printf("Mutex lock by thread succeed\n");
    else
        printf("Mutex lock by thread failed\n"); */
    
    pthread_mutex_t *mutexes = ptr;
    int id = 1;

    if (pthread_mutex_lock(mutexes) == 0)
        printf("Thread %d: Resource 1 secured\n", id);
    // One way to prevent deadlock:
    // When the required mutex (resource) is locked, unlock the resources it is
    // holding (locking).
    while (pthread_mutex_trylock(&mutexes[1]))
    {
        printf("Thread %d: Resource 2 not secured\n", id);
        pthread_mutex_unlock(&mutexes[0]);
        sleep(2);
        pthread_mutex_trylock(&mutexes[0]);
    }
    printf("Thread %d: Resource 2 secured\n", id);
    
    sleep(2);
    if (   pthread_mutex_unlock(&mutexes[0]) == 0
        && pthread_mutex_unlock(&mutexes[1]) == 0)
    {
        printf("Thread %d: Resources unlocked\n", id);
    }
    printf("Thread %d: finished\n", id);
    pthread_exit(NULL);
}

void *resource2(void *ptr)
{
    pthread_mutex_t *mutexes = ptr;
    int id = 2;

    printf("Thread %d\n", id);
    if (pthread_mutex_lock(mutexes + 1) == 0)
        printf("Thread %d: Resource 2 secured\n", id);
    while (pthread_mutex_trylock(&mutexes[0]))
    {
        printf("Thread %d: Resource 1 not secured\n", id);
        pthread_mutex_unlock(&mutexes[1]);
        sleep(3);
        pthread_mutex_trylock(&mutexes[1]);
    }
    printf("Thread %d: Resource 1 secured\n", id);

    sleep(3);
    if (   pthread_mutex_unlock(&mutexes[0]) == 0
        && pthread_mutex_unlock(&mutexes[1]) == 0)
    {
        printf("Thread %d: Resources unlocked\n", id);
    }
    printf("Thread %d: finished\n", id);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    // Two to declare a mutex
    // 1. statically:
    pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
    // 2. dynamically:
    pthread_mutex_t mutex2;
    pthread_mutex_init(&mutex2, NULL);


    pthread_t       t1;
    pthread_t       t2;
    pthread_mutex_t mutexes[2];

    pthread_mutex_init(&mutexes[0], NULL);
    pthread_mutex_init(&mutexes[1], NULL);

    printf("Creating thread 1\n");
    if (pthread_create(&t1, NULL, resource1, (void *)(mutexes)))
        printf("Failed\n");
    printf("Creating thread 2\n");
    if (pthread_create(&t2, NULL, resource2, (void *)(mutexes)))
        printf("Failed\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutexes[0]);
    pthread_mutex_destroy(&mutexes[1]);

}
