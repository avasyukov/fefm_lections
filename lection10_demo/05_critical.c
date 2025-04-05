#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long counter = 0;

    #pragma omp parallel
    {
        #pragma omp critical
        {
            for (int i = 0; i < 10000000; i++) {
                counter++;
            }
        }
    }

    printf("Value: %ld\n", counter);

    return 0;
}