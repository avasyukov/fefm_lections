#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

int main() {
    const int N = 100'000'000;
    vector<double> vec(N);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    #pragma omp parallel for
    for(int i = 0; i < N; ++i) {
        vec[i] = sin(M_PI * float(i) / N);
    }

    double sum = 0;
    double step = 1 / (double)N;

    #pragma omp parallel for
    for(int i = 0; i < N; ++i) {
        sum += vec[i] * step * M_PI;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Result: " << sum << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    return 0;
}