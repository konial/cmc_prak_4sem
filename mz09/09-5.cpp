#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<char, std::vector<char>> tree;
bool visited[26];

void dfs(char state) {
    visited[state - 'A'] = true;
    for (auto it : tree[state]) {
        if (!visited[it - 'A']) {
            dfs(it);
        }
    }
}


int main() {
    char left;
    std::string right;
    std::map<char, std::vector<std::string>> grammar;
    while (std::cin >> left >> right) {
        for (auto it : right) {
            if (isupper(it)) {
                tree[left].push_back(it);
            }
        }
        grammar[left].push_back(right);
    }

    dfs('S');

    for (auto it : grammar) {
        if (visited[it.first - 'A']) {
            for (auto itt : it.second) {
                std::cout << it.first << ' ' << itt << std::endl;
            }
        }
    }

    return 0;
}
