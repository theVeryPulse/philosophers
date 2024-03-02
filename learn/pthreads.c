#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_args
{
    int n;
    char c;
    char *s;
}   t_args;

pthread_attr_t attr;

/** 
 * The function for the new thread to execute.
 * It is good practice to end thread function with pthread_exit().
 *  
 */
void *routine(void *args)
{
    size_t stack_size;

    printf("Test from threads:\n");
    printf("Thread ID:\t%ld\n", pthread_self());
    printf("Num:\t\t%d\n", ((t_args *)args)->n);
    printf("Char:\t\t'%c'\n", ((t_args *)args)->c);
    printf("Str:\t\t\"%s\"\n", ((t_args *)args)->s);

    char *ptr = strdup("Returned string from thread function");
    pthread_exit((void *)ptr);
}

/**
 * By default, threads are created joinable.
 * Joinable threads can be converted to detached (not-joinable) by
 * pthread_detach().
 */
void *detached_thread(void *ptr)
{
    pthread_detach(pthread_self());
    sleep(1);
    printf("Detached thread after sleep(1)\n");
    pthread_exit(NULL);
}

void once_msg(void)
{
    printf("pthread_once(), this message should be displayed only once\n");
}

int main(int argc, char const *argv[])
{
    size_t stack_size;

    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("Default stack size: %li bytes\n", stack_size);

    stack_size = 90000000; // 9MBs
    pthread_attr_setstacksize(&attr, stack_size);
    printf("New stack size: %li bytes\n", stack_size);


    // First Thread
    pthread_t t1 = 0;
    t_args args;

    args.n = 42;
    args.c = 'c';
    args.s = "string";
    // 3rd arg: function for new thread to execute
    // 4th arg: argument for the function
    if (pthread_create(&t1, &attr, routine, (void *)(&args)) != 0)
        fprintf(stderr, "Failed to create a thread.\n");
    printf("Created thread with ID: %ld\n", t1);

    char *returned_val;
    pthread_join(t1, (void **)(&returned_val));
    printf("Return value: %s\n", returned_val);
    free(returned_val);
    returned_val = NULL;


    // Second Thread
    pthread_t t2 = 0;
    if (pthread_create(&t2, NULL, detached_thread, NULL) != 0)
        fprintf(stderr, "Failed to create a thread.\n");

    // Compare two thread ids
    if (pthread_equal(t1, t2) == 0) // Returns 0 if two threads are different
        printf("Two threads with different ids checked by pthread_equal().\n");

    // Executes a routine only once for different threads
    pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, once_msg);
    pthread_once(&once, once_msg);


    // Using pthread_exit() in main will end the thread running the main,
    // function but leave all other threads intact
    pthread_exit(NULL);
}
