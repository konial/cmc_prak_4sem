#include <vector>
#include <cstdint>

void
process(std::vector<int64_t> &vec, int64_t val)
{
    int cnt = 0;
    for (auto elem : vec) {
        if (elem >= val) {
            ++cnt;
        }
    }

    size_t sz = vec.size();
    vec.resize(sz + cnt);
    auto iter = vec.begin() + sz;
    for (auto it = vec.begin() + sz; it != vec.end(); ++it) {
        while (*--iter < val);
        *it = *iter;
    }
}
