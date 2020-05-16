#include <iostream>
#include <algorithm>

int main()
{
    int m, n;
    std::cin >> m >> n;
    int x1, y1, x2, y2;
    while (std::cin >> x1 >> y1 >> x2 >> y2) {
        std::cout << std::min(abs(x1 - x2), std::min(x1, x2) + m - std::max(x1, x2))
            + std::min(abs(y1 - y2), std::min(y1, y2) + n - std::max(y1, y2))
            << std::endl;
    }
    return 0;
}
