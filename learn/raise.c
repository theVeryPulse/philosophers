#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void foo(int a) {
    printf("%d\n", a);
}

// void (*signal(int sig, void (*func)(int)))(int);

int main(int argc, char const *argv[]) {
    signal(SIGUSR1, foo);
    signal(SIGUSR2, foo);
    raise(SIGUSR1);
    signal(SIGUSR1, SIG_DFL);
    return 0;
}
