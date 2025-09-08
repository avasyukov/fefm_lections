#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int counter;

void* increase_counter(void *args) {
    counter += 1;
    sleep(1);
    printf("Thread %ld has counter value %d\n", pthread_self(), counter);
    return NULL;
}

int main() {
    counter = 0;

    pthread_t p[10];
    for (int i = 0; i < 10; ++i) {
        pthread_create(&p[i], NULL, increase_counter, NULL);
    }

    for (int i = 0; i < 10; ++i) {
        pthread_join(p[i], NULL);
    }

    return 0;
}