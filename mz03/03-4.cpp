#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>

class Sum
{
    double sum;
public:
    Sum() : sum(0) {};
    void operator()(double val) { sum += val; }
    double get() { return sum; }
};

void cut(std::vector<double> &exp)
{
    int count = 0.1 * exp.size();
    exp.erase(exp.begin(), exp.begin() + count);
    exp.erase(exp.end() - count, exp.end());
}

int main()
{
    std::vector<double> exp;
    double val;
    while (std::cin >> val)
    {
        exp.push_back(val);
    }

    cut(exp);
    std::sort(exp.begin(), exp.end());
    cut(exp);

    Sum s = std::for_each(exp.begin(), exp.end(), Sum());
    std::cout << std::setprecision(10) << s.get() / exp.size() << std::endl;
    return 0;
}
