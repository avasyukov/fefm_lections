#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int counter;

void* increase_counter(void *args) {
    int local_counter = counter;
    counter += 1;
    sleep(1);
    printf("Thread %ld has counter value %d\n", pthread_self(), local_counter);
    return NULL;
}

int main() {
    counter = 0;

    pthread_t p[128];
    for (int i = 0; i < 128; ++i) {
        pthread_create(&p[i], NULL, increase_counter, NULL);
    }

    for (int i = 0; i < 128; ++i) {
        pthread_join(p[i], NULL);
    }

    printf("Main has counter value %d\n", counter);
    return 0;
}
