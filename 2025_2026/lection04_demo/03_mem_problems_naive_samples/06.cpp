#include <iostream>

using namespace std;

void memory_leak() {
    int* arr = new int[100]; // Leak: no delete[]
}

void invalid_access() {
    int* arr = new int[5];
    arr[10] = 42; // Out-of-bounds write
    delete[] arr;
}

void use_uninitialized() {
    int x; // Uninitialized
    cout << "x = " << x << endl;
}

int main() {
    memory_leak();
    invalid_access();
    use_uninitialized();
    return 0;
}
