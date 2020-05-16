/*
Function "func" calculates result depending on conditions from problem 07-2.
It uses exception mechanism instead of "return", where "throw" type is "Result".
*/

#include <iostream>

class Result {
    long long res;
public:
    Result(long long res) : res(res) {}
    long long get() { return res; }
};

void func(long long a, long long b, unsigned k)
{
    if (k == 0) {
        Result result(a + b);
        throw result;
    }
    else if (b == 1) {
        Result result(a);
        throw result;
    }

    try {
        if (b > 1) {
            func(a, b - 1, k);
        }
    }
    catch (Result result) {
        try {
            func(a, result.get(), k - 1);
        }
        catch (Result result) {
            throw result;
        }
    }
}

int main()
{
    long long a, b;
    unsigned k;

    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        }
        catch (Result result) {
            std::cout << result.get() << std::endl;
        }
    }

    return 0;
}
