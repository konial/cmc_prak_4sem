#include <iostream>

class A
{
    int a;
    bool flag;
public:
    A() : flag(false)
    {
        std::cin >> a;
    }
    A(const A &ob) : flag(true)
    {
        std::cin >> a;
        a += ob.a;
    }
    ~A()
    {
        if (flag) { std::cout << a << std::endl; }
    }
};
