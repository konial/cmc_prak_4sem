#include <iostream>
#include <string>

bool check_terms(const std::string &str)
{
    for (size_t i = 0; i < str.size(); ++i) {
        if (isupper(str[i])) {
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
    bool terms_only = false;
    bool first_has_S = false;
    bool second_contains_S = false;
    bool is_free = true;
    bool is_inconclusing = true;
    bool flag = false;
    bool particular_case = false;
    std::string first, second;
    while (std::cin >> first >> second) {
        flag = true;
        terms_only = check_terms(first) ? true : terms_only;
        if (terms_only) { break; }
        first_has_S = (first == "S" ? true : first_has_S);
        second_contains_S = check_S(second) ? true : second_contains_S;
        is_inconclusing = (first.size() > second.size() ? false : is_inconclusing);
        is_inconclusing = ((second == "_" && !(first == "S")) ? false : is_inconclusing);
        is_free = ((check_terms(first) || first.size() != 1) ? false : is_free);
        particular_case = ((second == "_" && first == "S") ? true : particular_case);
        
    }

    bool is_appropriate = (particular_case && !second_contains_S) || !particular_case;

    if (!flag || terms_only || !first_has_S) {
        std::cout << -1 << std::endl;
    } else if (is_free && (!is_inconclusing || !is_appropriate)) {
        std::cout << 2 << std::endl;
    } else if (is_free && is_inconclusing && is_appropriate) {
        std::cout << 23 << std::endl;
    } else {
        std::cout << 10 << std::endl;
    }

    return 0;
}
