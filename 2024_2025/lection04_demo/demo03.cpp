#include <iostream>

using namespace std;

struct demo {
    bool b;
    int i;
    long l;
};

int main()
{
    demo d;
    d.b = true;
    d.i = 42;
    d.l = 42;

    cout << boolalpha << &(d.b) << " " << &(d.i) << " " << &(d.l) << endl;

    cout << sizeof(d.b) << endl;
    cout << sizeof(d.i) << endl;
    cout << sizeof(d.l) << endl;
    cout << sizeof(d) << endl;

    return 0;
}
