#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

#define THREADS_NUM 5

atomic_long counter;

void* increase_counter(void *args) {
    for (int i = 0; i < 10000000; i++ ) {
        counter++;
    }
    return NULL;
}

int main() {
    counter = 0;

    pthread_t p[THREADS_NUM];

    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_create(&p[i], NULL, increase_counter, NULL);
//        pthread_join(p[i], NULL);
    }

    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_join(p[i], NULL);
    }

    printf("Value: %ld\n", counter);

    return 0;
}