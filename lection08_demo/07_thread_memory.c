#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int value;

void* thread_task(void *message)
{
    printf("%s\n", (const char *) message);

    printf("value = %d\n", value);
    value++;
    printf("value = %d\n", value);

    return NULL;
}

int main (void)
{
    pthread_t thing1, thing2;
    int i1, i2;
    const char *message1 = "thing 1";
    const char *message2 = "thing 2";

    // Start threads
    i1 = pthread_create(&thing1, NULL, thread_task, (void *) message1);
    sleep(3);
    i2 = pthread_create(&thing2, NULL, thread_task, (void *) message2);

    // We must join here to wait for the threads to exit or the main thread may terminate first
    pthread_join (thing1, NULL);
    pthread_join (thing2, NULL);

    return 0;
}