#include <iostream>
#include <string>

class Print {
    std::string str;
public:
    Print(std::string str) : str(str) {}
    ~Print() {
        std::cout << str << std::endl;
    }
};

void func() {
    std::string str;
    if (std::cin >> str) {
        try {
            func();
        } catch (int i) {
            Print print(str);
            throw 0;
        }
    }
    throw 0;
}
int main()
{
    try {
        func();
    } catch (int i) {}
    return 0;
}
