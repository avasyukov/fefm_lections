#include <iostream>

using namespace std;

void run_test(int i)
{
    char* mem = new char[1024];
    mem[i] = 'A';
    /* delete[] mem; */
}

int main()
{
    for(int i = 0; i < 10; i++) {
        run_test(i);
    }
    return 0;
}
