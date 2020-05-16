#include <iostream>
#include <string>

bool check(const std::string &str) {
    enum state {S, A, B, C, ERROR, OK};
    state st = S;

    if (str.begin() == str.end()) { return false; }
    auto it = str.end() - 1;

    do {
        switch (st) {
        case S:
            if (( *it == '0' || *it == '1') && it != str.begin()) {
                if (it == str.begin()) {
                    st = OK;
                } else {
                    st = C;
                    --it;
                }
            }
            else {
                st = ERROR;
            }
            break;
        case A:
            if (*it == '0' || *it == '1') {
                if (it == str.begin()) {
                    st = OK;
                } else {
                    --it;
                }
            }
            else {
                st = ERROR;
            }
            break;
        case B:
            if (*it == '1') {

                if (it == str.begin()) {
                    st = OK;
                } else {
                    st = A;
                    --it;
                }
            }
            else {
                st = ERROR;
            }
            break;
        case C:
            if ((*it == '0' || *it == '1') && it != str.begin()) {
                if (it == str.begin()) {
                    st = OK;
                } else {
                    st = B;
                    --it;
                }
            }
            else {
                st = ERROR;
            }
            break;
        default:
            break;
        }
    } while (st != OK && st != ERROR);

    return st == OK;
}

int main() {
    std::string str;
    while (std::cin >> str) {
        std::cout << check(str) << std::endl;
    }

    return 0;
}
