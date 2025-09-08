#include <iostream>
#include <chrono>

#define N 1024

float a[N][N];
float b[N][N];
float c[N][N];

void init_matrix() {
    unsigned long long int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = random()/RAND_MAX;
            b[i][j] = random()/RAND_MAX;
        }
    }
}

void mult() {
    unsigned long long int i, j, k;
    
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
}

int main() {

    init_matrix();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    mult();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    return 0;
}
