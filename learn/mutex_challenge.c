#include <pthread.h>
#include <stdio.h>

typedef struct s_vars
{
    pthread_mutex_t *mutex_ptr;
    pthread_cond_t *cond_even_ptr;
    pthread_cond_t *cond_odd_ptr;
    int *data;
}   t_vars;

int counter = 0;

void *increment(void *ptr)
{
    t_vars *vars;
    
    vars = (t_vars *)ptr;
    pthread_mutex_lock(vars->mutex_ptr);

    while (*(vars->data) % 2 != 0
        || (*(vars->data) % 2 == 0 && *(vars->data) != 10))
    {
        pthread_cond_signal(vars->cond_ptr);
        pthread_cond_wait(vars->cond_ptr, vars->mutex_ptr);
    }
    /* printf("ID: %ld\tmessage: %d\tcounter: %d\n",
            pthread_self(),
            *(vars->data),
            counter); */
    counter++;
    printf("ID: %ld\tmessage: %d\tcounter: %d\n",
            pthread_self(),
            *(vars->data),
            counter);
    pthread_mutex_unlock(vars->mutex_ptr);
    if (*(vars->data) % 2 == 0)
    {
        pthread_cond_signal(vars->cond_ptr);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_mutex_t mutex;
    pthread_t threads[10];
    int data[10];
    t_vars vars[10];
    pthread_cond_t cond;

    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 10; i++)
    {
        data[i] = i + 1;
        vars[i].mutex_ptr = &mutex;
        vars[i].cond_ptr = &cond;
        vars[i].data = &data[i];
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, increment, (void *)(&vars[i]));
    }
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);
    pthread_join(threads[6], NULL);
    pthread_join(threads[7], NULL);
    pthread_join(threads[8], NULL);
    pthread_join(threads[9], NULL);
    pthread_exit(NULL);
}
