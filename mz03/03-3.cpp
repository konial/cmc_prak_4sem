#include <vector>
#include <algorithm>

void process(const std::vector<int> &v1, std::vector<int> &v2)
{
    std::vector<int> vec(v1);
    std::sort(vec.begin(), vec.end());
    std::vector<int>::iterator last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    std::vector<int>::iterator left_it = v2.begin();
    std::vector<int>::iterator right_it = v2.begin();

    int cnt = 0;
    for (std::vector<int>::iterator it = vec.begin(); right_it != v2.end(); ++right_it)
    {
        while (it != vec.end() && *it < std::distance(v2.begin(), right_it)) { ++it; }
        if (it != vec.end() && *it == std::distance(v2.begin(), right_it)) { ++cnt; }
        else { std::swap(*left_it++, *right_it); }
    }
    v2.resize(v2.size() - cnt);
}
