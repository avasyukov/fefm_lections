#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define JOBS_NUM 4  // number of jobs for each worker

int main() {
    #pragma omp parallel
    {
        for (int i = 0; i < JOBS_NUM; i++) {
            printf("Worker %d: Doing Job %d\n", omp_get_thread_num(), i);
            #pragma omp barrier
        }
    }

    return 0;
}