#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    struct timeval time;

    while (true)
    {
        gettimeofday(&time, NULL);
        printf("tv_sec: %ld tv_usec: %ld in ms: %lld\n",
            time.tv_sec,
            time.tv_usec,
            time.tv_sec * (long long)1000 + time.tv_usec / (long long)1000);
        usleep(10000);
    }

    return 0;
}
