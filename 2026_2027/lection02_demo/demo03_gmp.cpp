#include <iostream>
#include <iomanip>
#include <gmpxx.h>

using namespace std;

int main()
{
    mpf_set_default_prec(256);
    mpf_class a("0.1");
    mpf_class b("0.2");
    mpf_class c = a + b;

    cout << fixed << setprecision(32);

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
