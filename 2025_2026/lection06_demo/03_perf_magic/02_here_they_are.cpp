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
    double x0 = 1;
    double x1 = 1;
    double x2 = 1;
    double x3 = 1;
    double x4 = 1;
    double x5 = 1;

    // Работа с 6 накопителями
    // Достаточное <<правильное>> число зависит от процессора
    for (i = 0; i < SIZE; i+=6) {
        x0 = x0 * a[i];
        x1 = x1 * a[i+1];
        x2 = x2 * a[i+2]; 
        x3 = x3 * a[i+3];
        x4 = x4 * a[i+4];
        x5 = x5 * a[i+5];
    }
    // Учёт оставшихся элементов в накопителе x0
    for (; i < SIZE; i++) {
        x0 = x0 * a[i];
    }
    // Сборка итогового результата из накопителей
    result = x0 * x1 * x2 * x3 * x4 * x5;

    std::cout << "Res = " << result << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    delete[] a;

    return 0;
}
