#include <iostream>
#include <string>

bool check_terms(std::string::const_iterator it1, std::string::const_iterator it2)
{
    for (; it1 != it2; ++it1) {
        if (isupper(*it1)) {
            return false;
        }
    }
    return true;
}

bool check_S(const std::string &str)
{
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == 'S') {
            return true;
        }
    }
    return false;
}

int main()
{
    bool second_contains_S = false;
    bool is_inconclusing = true;
    bool particular_case = false;
    bool is_left = true;
    bool is_right = true;
    bool is_left_automat = true;
    bool is_right_automat = true;
    std::string first, second;
    while (std::cin >> first >> second) {
        second_contains_S = check_S(second) ? true : second_contains_S;
        
        is_inconclusing = (first.size() > second.size()) ? false : is_inconclusing;
        is_inconclusing = (second == "_" && first != "S") ? false : is_inconclusing;
        
        particular_case = (second == "_" && first == "S") ? true : particular_case;
        
        is_left = isupper(second.front()) && !check_terms(second.begin() + 1, second.end())
            ? false : is_left;
        is_left = !isupper(second.front()) && !check_terms(second.begin(), second.end())
            ? false : is_left;

        is_right = isupper(second.back()) && !check_terms(second.begin(), second.end() - 1)
            ? false : is_right;
        is_right = !isupper(second.back()) && !check_terms(second.begin(), second.end())
            ? false : is_right;

        is_left_automat = (second == "_" && first != "S") ? false : is_left_automat;
        is_left_automat = second.size() > 2 ? false : is_left_automat;
        is_left_automat = second.size() == 2 && (isupper(second.back()) || !isupper(second.front()))
            ? false : is_left_automat;
        is_left_automat = second.size() == 1 && isupper(second.front()) && first != "S"
            ? false : is_left_automat;

        is_right_automat = (second == "_" && first != "S") ? false : is_right_automat;
        is_right_automat = second.size() > 2 ? false : is_right_automat;
        is_right_automat = second.size() == 2 && (!isupper(second.back()) || isupper(second.front()))
            ? false : is_right_automat;
        is_right_automat = second.size() == 1 && isupper(second.front()) && first != "S"
            ? false : is_right_automat;
    }

    bool is_appropriate = (particular_case && !second_contains_S) || !particular_case;
    is_left_automat &= is_appropriate;
    is_right_automat &= is_appropriate;


    if (!is_inconclusing || !is_appropriate) {
        if (!is_left && !is_right) {
            std::cout << 2 << std::endl;
        }
    } else {
        if (!is_left && !is_right) {
            std::cout << 21 << std::endl;
        }
    }
    
    if (is_left && !is_left_automat) {
        std::cout << 31 << std::endl;
    } else if (is_right && !is_right_automat) {
        std::cout << 32 << std::endl;
    } else if (is_left_automat) {
        std::cout << 311 << std::endl;
    } else if (is_right_automat) {
        std::cout << 321 << std::endl;
    }

    return 0;
}
