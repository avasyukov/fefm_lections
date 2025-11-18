#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    float a = 0.1;
    float b = 0.2;
    float c = a + b;

    cout << fixed << setprecision(32);

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
