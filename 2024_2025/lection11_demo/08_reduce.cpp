#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>

// Creates an array of random numbers
float *create_rand_nums(int num_elements) {
    float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++) {
        rand_nums[i] = (rand() / (float)RAND_MAX);
    }
    return rand_nums;
}

// Computes the average of an array of numbers
float compute_avg(float *array, int num_elements) {
    float sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int num_elements_per_proc = 1000;

    // Create a random array of elements on the root process. Its total
    // size will be the number of elements per process times the number
    // of processes
    float *rand_nums = NULL;
    if (world_rank == 0) {
        rand_nums = create_rand_nums(num_elements_per_proc * world_size);
    }

    // For each process, create a buffer that will hold a subset of the array
    float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);

    // Scatter the random numbers from the root process to all processes
    MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT,
                sub_rand_nums, num_elements_per_proc, MPI_FLOAT,
                0, MPI_COMM_WORLD);

    // Compute the average of your subset
    float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

    printf("Local result of process %d is %f\n", world_rank, sub_avg);

    float sum_of_all_avgs;
    MPI_Reduce(&sub_avg, &sum_of_all_avgs, 1, MPI_REAL, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Global result is %f\n", sum_of_all_avgs / world_size);

        // Compute the average across the original data for comparison
        float original_data_avg = compute_avg(rand_nums, num_elements_per_proc * world_size);
        printf("Avg computed across original data is %f\n", original_data_avg);
    }

    // Clean up
    if (world_rank == 0) {
        free(rand_nums);
    }
    free(sub_rand_nums);

    MPI_Finalize();

    return 0;
}