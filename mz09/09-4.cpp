#include <iostream>

//S = P
//P = aPd | Q
//Q = bQc | eps

void Q(int cnt) {
    std::cout << 'b';
    if (cnt > 0) {
        Q(cnt - 1);
    }
    std::cout << 'c';
}

void P(int k, int cnt) {
    std::cout << 'a';
    if (cnt > 0) {
        P(k, cnt - 1);
    }
    if (cnt == 0) {
        Q(k);
    }
    std::cout << 'd';
}

void S(int k, int cnt) {
    P(k / 2 - cnt - 2, cnt);
    std::cout << std::endl;
    if (cnt > 0) {
        S(k, cnt - 1);
    }
}


int main() {
    int k;
    std::cin >> k;

    if (k % 2 == 0 && k >= 4) {
        S(k, (k - 2) / 2 - 1);
    }

    return 0;
}
