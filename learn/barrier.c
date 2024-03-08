#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void *func(void *barrier)
{
    printf("Waiting at barrier.\n");
    sleep(2);
    pthread_barrier_wait((pthread_barrier_t *)barrier);
    printf("Through barrier.\n");
}

int main(int argc, char const *argv[]) 
{
    int thread_count = 6;
    pthread_barrier_t barrier;
    pthread_t threads[thread_count];

    // Wait until five threads arrive at barrier
    pthread_barrier_init(&barrier, NULL, thread_count);

    for (int i = 0; i < thread_count; i++)
    {
        pthread_create(&threads[i], NULL, func, (void *)&barrier);
    }

    for (int i = 0; i < thread_count; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
