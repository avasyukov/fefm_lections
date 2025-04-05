#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_barrier_t barrier;

#define THREADS_NUM 3   // number of workers
#define JOBS_NUM 4      // number of jobs for each worker

void* worker_thread(void *data) {
    for (int i = 0; i < JOBS_NUM; i++) {
        printf("Worker %ld: Doing Job %d\n", pthread_self(), i);
        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

int main() {
    pthread_t p[THREADS_NUM];

    pthread_barrier_init(&barrier, NULL, THREADS_NUM);

    for (int i = 0; i < THREADS_NUM; i++) {
        pthread_create(&p[i], NULL, worker_thread, NULL);
    }

    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_join(p[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
