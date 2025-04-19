#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <cstddef>

#define SIZE 5

typedef struct custom {
    double a1;
    double a2;
} custom;

void define_struct(MPI_Datatype *type) {
    const int count = 2;
    int          blocks_length[count] = {1, 1};
    MPI_Datatype basic_types[2] = {MPI_DOUBLE, MPI_DOUBLE};
    MPI_Aint     blocks_displacements[count] = {offsetof(custom, a1), offsetof(custom, a2)};

    MPI_Type_create_struct(count, blocks_length, blocks_displacements, basic_types, type);
    MPI_Type_commit(type);
};

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    custom info[SIZE];

    // Just adding some values
    if(world_rank == 0) {
        for(int i = 0; i < SIZE; i++) {
            info[i].a1 = i * i;
            info[i].a2 = i * (i+1);
        }
    }

    // Create MPI types
    MPI_Datatype struct_type;
    define_struct(&struct_type);

    MPI_Bcast(info, 5, struct_type, 0, MPI_COMM_WORLD);

    if(world_rank != 0) {
        for(int i = 0; i < SIZE; i++) {
            printf("%lf %lf\n", info[i].a1, info[i].a2);
        }
    }

    MPI_Finalize();

    return 0;
}