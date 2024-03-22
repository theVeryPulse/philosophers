#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static void handler(int sig, siginfo_t *siginfo, void *content)
{
    printf("Sender PID: %ld\n", (long)siginfo->si_pid); 
    printf("UID: %ld\n", (long)siginfo->si_uid);

}

int main()
{
    struct sigaction sa;


    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if
                                 interrupted by handler */
    if (sigaction(SIGINT, &sa, NULL) == -1)
        /* Handle error */;
    char c;
    read(STDIN_FILENO, &c, 1);
    raise(SIGINT);

    /* Further code */
}

