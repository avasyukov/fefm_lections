#include<iostream>

using namespace std;

int f_p(int i)
{
    return i * i;
}

int f_q(int i)
{
    return i * i * i;
}

int main()
{
    int a;
    int b;
    cin >> a;
    cin >> b;

    int q = f_q(a);
    int p = f_p(b);

    int res = p + q;

    cout << res << endl;
    return 0;
}
