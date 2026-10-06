#include <iostream>
#include <vector>
#include <chrono>
#include <gmpxx.h>

// Нас интересует умножение двух больших матриц как пример вычислительно нагруженной операции.
// Это базовая реализация, с которой мы будем сверяться.
// Данная реализация на C++ не идеальна, здесь есть что оптимизировать и улучшить.
// Тем не менее, откровенной грязи в этой реализации тоже нет, а обход матриц при умножении написан cache friendly.
// Поэтому возьмём этот код за отправную точку по времени выполнения.
// На забудьте его собрать с уровнем оптимизации O2 или O3.

// Матрицы у нас NxN, где N задаётся вот этим define-ом.
// Разумные размеры для тестирования на лаптопе/десктопе - где-то от 256 до 2048.

#define N 400

using namespace std;

// Инит матрицы случайными числами
void init_matrix(vector<vector<mpf_class>>& m) {
    unsigned long size = m.size();
    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = 0; j < size; ++j) {
            m[i][j] = (double)rand() / RAND_MAX;
        }
    }
};

// Вывод матрицы (на самом деле не используется)
void print_matrix(vector<vector<mpf_class>>& m) {
    unsigned long size = m.size();
    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = 0; j < size; ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
};

// Собственно умножение
void mult(vector<vector<mpf_class>>& c, const vector<vector<mpf_class>>& a, const vector<vector<mpf_class>>& b) {
    unsigned long size = c.size();
    unsigned long i, j, k;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            c[i][j] = 0;
        }
    }
    
    for (k = 0; k < size; ++k) {
        for (i = 0; i < size; ++i) {
            for (j = 0; j < size; ++j) {
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
};

int main() {
    mpf_set_default_prec(256);

    vector<vector<mpf_class>> a(N, vector<mpf_class>(N, 0));
    vector<vector<mpf_class>> b(N, vector<mpf_class>(N, 0));
    vector<vector<mpf_class>> c(N, vector<mpf_class>(N, 0));

    // Инициализируем матрицы a и b
    init_matrix(a);
    init_matrix(b);

    std::cout << "Size: " << N << std::endl;

    // Получим c = a * b, измерим время этой операции
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    mult(c, a, b);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - begin;

    std::cout << "Time: " 
        << std::chrono::duration_cast<std::chrono::duration<double>>(diff).count()
        << " (" << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << " µs)" << std::endl;

    return 0;
}
