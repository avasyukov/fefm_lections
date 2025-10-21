#include <iostream>

using namespace std;

int main() {
    char* destination = new char[27];
    char* source = new char[26];

    for(int i = 0; i < 27; i++) {
        destination[i] = source[i]; //Look at the last iteration.
    }

    delete[] destination;
    delete[] source;
    return 0;
}
