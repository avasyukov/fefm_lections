#include <stdio.h>
#include <pthread.h>

/* Two worker threads claim the same two locks, but 
 * do so in a different order. This means we can end 
 * up in a situation where each thread holds one of the 
 * locks and is waiting for the lock held by the other. 
 */

void* s_worker_1(void *arg) {
    pthread_mutex_t *locks = arg;
    pthread_mutex_lock(&locks[0]);
    pthread_mutex_lock(&locks[1]);
    printf("Thread 1 - both locks locked\n");
    pthread_mutex_unlock(&locks[1]);
    pthread_mutex_unlock(&locks[0]);
    return NULL;
}

void* s_worker_2(void *arg) {
    pthread_mutex_t *locks = arg;
    pthread_mutex_lock(&locks[1]);
    pthread_mutex_lock(&locks[0]);
    printf("Thread 2 - both locks locked\n");
    pthread_mutex_unlock(&locks[0]);
    pthread_mutex_unlock(&locks[1]);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_t locks[2];
    pthread_mutex_init(&locks[0], NULL);
    pthread_mutex_init(&locks[1], NULL);
    pthread_create(&t1, NULL, s_worker_1, locks);
    pthread_create(&t2, NULL, s_worker_2, locks);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}