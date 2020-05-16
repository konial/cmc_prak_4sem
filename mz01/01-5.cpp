#include <iostream>

// class Holder has given in the text of the problem

class Holder
{
    int value = 0;

public:
    Holder()
    {
        std::cin >> value;
    }

    ~Holder()
    {
        std::cout << value << std::endl;
    }

    void swap(Holder &other)
    {
        int tmp = value;
        value = other.value;
        other.value = tmp;
    }
};

int main()
{
    int count;
    std::cin >> count;

    Holder **ptr = new Holder*[count];
    for (int i = 0; i < count; ++i)
    {
        ptr[i] = new Holder();
    }
    for (int i = 0; i < count; ++i)
    {
        delete ptr[i];
    }

    return 0;
}
