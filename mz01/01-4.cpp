#include <iostream>
#include <cmath>

int main() {
    double a, sum1 = 0, sum2 = 0, n = 0, dev = 0;
    while(std::cin >> a) {
        sum1 += a;
        sum2 += a * a;
        ++n;
    }
    std::cout << std::fixed;
    std::cout.precision(10);
    std::cout << sum1 / n << std::endl;
    dev = sqrt((sum2 - sum1 * sum1 / n) / n);
    std::cout << dev << std::endl;
}
