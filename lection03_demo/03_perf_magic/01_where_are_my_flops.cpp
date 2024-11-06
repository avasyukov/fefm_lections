#include <iostream>
#include <chrono>

#define SIZE 1000*1000*1000

int main()
{
    long i;
    double* a = new double[SIZE];
    for(i = 0; i < SIZE; i++) {
        a[i] = random()/RAND_MAX;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    double result = 1;
    for(i = 0; i < SIZE; i++) {
        result = result * a[i];
    }

    std::cout << "Res = " << result << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    delete[] a;

    return 0;
}
