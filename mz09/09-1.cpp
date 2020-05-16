#include <iostream>
#include <vector>
#include <string>

bool check(const std::string &str)
{
    std::vector<char> symbols { 'a', '0', 'b', '1' };
    std::vector<int> cnts(4);

    auto cur_symb = symbols.begin();
    auto cur_cnt = cnts.begin();

    for (auto it : str) {
        if (it != *cur_symb) {
            if (cur_symb + 1 == symbols.end()) {
                return false;
            } else if (it != *(cur_symb + 1)) {
                return false;
            }
            ++cur_symb;
            ++cur_cnt;
        }
        ++(*cur_cnt);
    }

    return (cnts[0] == cnts[2] && cnts[1] == cnts[3]);
}

int main()
{
    std::string str;
    while (std::cin >> str) {
        std::cout << check(str) << std::endl;
    }

    return 0;
}
