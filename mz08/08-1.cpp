#include <iostream>
#include <string>

bool is_belong(const std::string &str) {
    bool is_postfix = false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '3' || str[i] == '4') {
            if (is_postfix) {
                return 0;
            }
        } else if(str[i] == '1' || str[i] == '2') {
            is_postfix = true;
        } else {
            return 0;
        }
    }
    return 1;
}


int main()
{
    std::string str;
    while (std::cin >> str) {
        std::cout << is_belong(str) << std::endl;
    }

    return 0;
}
