#include <cstdio>
#include <time.h>

class Direct
{
public:
    int perform(int &ia) { return ++ia; }
};

class Base
{
public:
    virtual int perform(int &ia) = 0;
};

class Derived: public Base
{
public:
    virtual int perform(int &ia) { return ++ia; }
};


int main()
{
    // Non-virtual calls
    Direct dir;
    Direct* pdir = &dir;

    int ia = 0;
    double start = clock();

    while( pdir->perform(ia) );

    double end = clock();
    printf("Direct %.3f, ia=%d\n", (end-start)/CLOCKS_PER_SEC, ia);

    // Virtual calls

    Derived drv;
    Base* ab = &drv;

    ia = 0;
    start = clock();

    while(ab->perform(ia));

    end = clock();
    printf("Virtual: %.3f, ia=%d\n", (end-start)/CLOCKS_PER_SEC, ia);

    return 0;
}
