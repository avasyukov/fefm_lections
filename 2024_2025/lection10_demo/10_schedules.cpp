#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <omp.h>

using namespace std;

int main() {
    const int N = 100'000;
    vector<double> vec(N);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    #pragma omp parallel for schedule(runtime)
    for(int i = 0; i < N; ++i) {
        vec[i] = sin(M_PI * float(i) / N);

        bool is_thread_even = (omp_get_thread_num() % 2 == 0);
        if (is_thread_even) {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    return 0;
}