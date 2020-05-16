#include <iostream>
#include <string>

enum state {S, A, B, C, D};

int main() {
    
    state st = S;
    std::string str;
    std::cin >> str;
    int cur = 0;
    bool flag = true;
    while (flag) {
        switch (st) {
        case S:
            if (str[cur++] == '1') {
                st = A;
            }
            break;
        case A:
            if (str[cur] == '0') {
                ++cur;
            }
            else if (str[cur] == '1') {
                ++cur;
                st = S;
            }
            else if (str[cur] == '#') {
                --cur;
                st = B;
            }
            break;
        case B:
            if (str[cur] == '0') {
                --cur;
            }
            else if (str[cur] == '1') {
                --cur;
            }
            else if (str[cur] == '#') {
                ++cur;
                st = C;
            }
            break;
        case C:
            if (str[cur] == '0') {
                ++cur;
            }
            else if (str[cur] == '1') {
                str[cur] = '0';
                st = D;
                flag = false;
            }
            break;
        case D:
            if (str[cur] == '0') {
                flag = false;
            }
            break;
        }
        if (cur < 0 || cur > (int)str.size() - 1) {
            flag = false;
        }
    }
    std::cout << str << std::endl;

    return 0;
}
