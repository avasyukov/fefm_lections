#include <mpi.h>
#include <cmath>
#include <iostream>

float fct(double x)
{
    return cos(x);
}

float integral(double a, long long n, double h)
{
    std::cout << "Starting from " << a << " and doing " << n << " steps with step " << h << std::endl;

    double local_result = 0.0;
    double h_half = h / 2.;

    for (long long j = 0; j < n; j++) {
        double x = a + j * h + h_half;
        local_result += fct(x) * h;
    }
    return (local_result);
}

int main(int argc, char *argv[])
{
    double a = 0;              // lower limit of integration
    double b = M_PI * 0.5;     // upper limit of integration
    long long n = 100000;      // number of steps
    double h = (b - a) / n;

    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    long long steps_per_process = n / world_size;
    double range_per_process = (b - a) / world_size;

    double my_left_border = a + world_rank * range_per_process;

    double my_local_result = integral(my_left_border, steps_per_process, h);

    std::cout << "Process " << world_rank << " has the partial result " << my_local_result << std::endl;

    if (world_rank == 0) {
        double result = my_local_result;

        for (int i = 1; i < world_size; i++) {
            int source = i;
            double remote_result;
            MPI_Recv(&remote_result, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Received remote result: " << remote_result << std::endl;
            result += remote_result;
        }
        std::cout << "The result is: " << result << std::endl;
    } else {
        MPI_Send(&my_local_result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        std::cout << "Sent local result: " << my_local_result << std::endl;
    }

    MPI_Finalize();

    return 0;
}