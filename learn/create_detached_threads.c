#include <pthread.h>
#include <stdio.h>

void *func(void *vars)
{
    printf("Detached thread.\n");
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    pthread_attr_t detached;

    pthread_attr_init(&detached);
    pthread_attr_setdetachstate(&detached, PTHREAD_CREATE_DETACHED);

    pthread_create(&thread, &detached, func, NULL);
    return 0;
}
