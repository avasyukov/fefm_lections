#include <mpi.h>
#include <iostream>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int broadcast_message = -1;
    if (world_rank == 0) {
        broadcast_message = 42;
    }

    // Broadcasting the message from process 0 to all other processes
    MPI_Bcast(&broadcast_message, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::cout << "Process " << world_rank << " received broadcast message " << broadcast_message << std::endl;

    MPI_Finalize();
    return 0;
}