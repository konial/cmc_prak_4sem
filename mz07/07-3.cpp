#include <iostream>
#include <utility>

class S {
    
public:
    int val;
    bool can_read;
    bool can_print;
    S() {
        can_read = std::cin >> val ? true : false;
        if (!can_read) {
            can_print = false;
        }
    }
    S(S &&v) {
        int a;
        can_read = std::cin >> a ? true : false;
        if (can_read) {
            val = v.val + a;
            v.can_print = false;
        } else {
            val = 0;
            can_print = false;
            v.can_print = true;
        }
    }
    ~S() {
        if (can_print) {
            std::cout << val << std::endl;
        }
    }
    operator bool() const { return can_read; }
};
