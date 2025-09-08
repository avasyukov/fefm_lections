#include <pthread.h>
#include <stdio.h>

#define THREADS_NUM 5

pthread_mutex_t lock;

long counter;

void* increase_counter(void *args) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 10000000; i++ ) {
        counter++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    counter = 0;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("mutex init has failed\n");
        return -1;
    }

    pthread_t p[THREADS_NUM];

    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_create(&p[i], NULL, increase_counter, NULL);
//        pthread_join(p[i], NULL);
    }

    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_join(p[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Value: %ld\n", counter);

    return 0;
}