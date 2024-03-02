#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // Dynamically create a condition variable
    pthread_cond_t cond1;
    pthread_cond_init(&cond1, NULL);
    // Statically create a condition variable
    pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

    pthread_mutex_t t1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&t1);
    pthread_cond_wait(&cond1, &t1);
    pthread_cond_timedwait(&cond1, &t1, 10);

    pthread_cond_signal(&cond1);
    pthread_cond_broadcast(&cond1);

    return 0;
}
