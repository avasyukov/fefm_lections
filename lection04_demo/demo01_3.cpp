#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double a = 0.1;
    double b = 0.4;

    double c = a + b;

    cout << fixed << setprecision(32);

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
