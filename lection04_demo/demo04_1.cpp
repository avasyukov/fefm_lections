#include <iostream>

using namespace std;

class animal {
public:
    void move() { cout << "...moved to ...\n"; }
    void speak() { cout << "(silence)\n"; }
};

class cow : public animal {
public:
    void speak() { cout << "Moo!\n"; }
};

class dog : public animal {
public:
    void speak() { cout << "Woof!\n"; }
};

class crazy_dog : public dog {
public:
    void speak() { cout << "Woof! Woof! Woof!\n"; }
};

void f(animal* p) {
    p->move();
    p->speak();
}

int main()
{
    cow obj1;
    dog obj2;
    crazy_dog obj3;

    f(&obj1);
    f(&obj2);
    f(&obj3);

    return 0;
}
