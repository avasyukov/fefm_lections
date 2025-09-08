#include <mpi.h>
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(world_rank != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Hello from process " << world_rank
              << " out of " << world_size
              << ", running on " << processor_name << "." << std::endl;

    MPI_Barrier(MPI_COMM_WORLD);

    if(world_rank == 0) {
        std::cout << "All processors reached the barrier. Proceeding." << std::endl;
    }

    MPI_Finalize();
    return 0;
}