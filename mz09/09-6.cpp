#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class DFSA {
    std::vector<char> alphabet;
    std::string start_state;
    std::vector<std::string> final_states;
    std::map<std::pair<std::string, char>, std::string> rules;
public:
    DFSA() {
        std::string cur_st;
        char c;
        std::string new_st;
        while (std::cin >> cur_st && cur_st != "END") {
            std::cin >> c >> new_st;
            rules[std::make_pair(cur_st, c)] = new_st;
        }

        std::string final_st;
        while (std::cin >> final_st && final_st != "END") {
            final_states.push_back(final_st);
        }

        std::cin >> start_state;
    }
    void analyze(std::string);
};

void DFSA::analyze(std::string str)
{
    std::string cur_st = start_state;
    bool appropriate = true;
    int cnt = 0;
    for (auto it : str) {
        const auto found = rules.find(std::make_pair(cur_st, it));
        if (found == rules.cend()) {
            appropriate = false;
            break;
        }
        else {
            cur_st = rules[found->first];
        }
        ++cnt;
    }
    if (std::find(final_states.begin(), final_states.end(), cur_st)
        == final_states.cend()) {
        appropriate = false;
    }

    std::cout << appropriate << std::endl;
    std::cout << cnt << std::endl;
    std::cout << cur_st << std::endl;
}

int main() {
    DFSA automat;

    std::string word;
    std::cin >> word;

    automat.analyze(word);

    return 0;
}
