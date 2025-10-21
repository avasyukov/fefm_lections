#include <iostream>

using namespace std;

int main() {
    char* alphabet = new char[26];

    for(int i = 0; i < 26; i++) {
        alphabet[i] = 'A' + i;
    }
    alphabet[26] = '\0'; //null-terminate the string?

    cout << alphabet << endl;

    delete[] alphabet;
    return 0;
}
