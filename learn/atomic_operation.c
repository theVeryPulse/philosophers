#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

atomic_int shared_counter = ATOMIC_VAR_INIT(0);

void* increment_counter(void* arg) {
    for (int i = 0; i < 10; ++i) {
        atomic_fetch_add(&shared_counter, 1);
        printf("%ld\n", pthread_self());
        printf("%ld\n", pthread_self());
    }
    return NULL;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Final value of counter: %d\n", atomic_load(&shared_counter));
    pthread_mutex_destroy(&thread1);
    pthread_mutex_destroy(&thread2);
    return (0);
}
