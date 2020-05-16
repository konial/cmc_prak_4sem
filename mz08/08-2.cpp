#include <iostream>
#include <string>

bool is_belong() {
    bool is_first = true;
    int zero_cnt = 0, one_cnt = 0;
    int zero_tmp_cnt = 0, one_tmp_cnt = 0;
    char first = '-', cur = ' ', prev = '-';

    while (isspace(cur)) {
        if (std::cin.eof()) {
            throw 0;
        }
        std::cin.get(cur);
    }
    std::cin.putback(cur);

    while (std::cin.get(cur) && !isspace(cur)) {
        if (prev == '-') {
            first = cur;
        }
        if (cur == '0') {
            //if new sequence starts
            if (prev == '1') {
                //if previous sequence was first
                if (is_first) {
                    zero_tmp_cnt = zero_cnt;
                    one_tmp_cnt = one_cnt;
                    is_first = false;
                }
                else {
                    //if current sequence wrong
                    if (zero_tmp_cnt != zero_cnt || one_tmp_cnt != one_cnt) {
                        while (std::cin.get(cur) && !isspace(cur));
                        return 0;
                    }
                }
                zero_cnt = 0;
                one_cnt = 0;
            }
            ++zero_cnt;
        }
        else if (cur == '1') {
            ++one_cnt;
        }
        else {
            while (std::cin.get(cur) && !isspace(cur));
            return 0;
        }
        prev = cur;
    }

    //checking extreme cases
    if (first != '0' || prev != '1') {
        return 0;
    }
    else if (is_first) {
        return 1;
    }
    else if (zero_tmp_cnt != zero_cnt || one_tmp_cnt != one_cnt) {
        return 0;
    }
    return 1;
}


int main()
{
    try {
        while (1) {
            std::cout << is_belong() << std::endl;
        }
    }
    catch (int a) {}

    return 0;
}
