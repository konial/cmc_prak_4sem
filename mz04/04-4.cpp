#include <utility>

template <class NmIter, class RmvIter>
RmvIter myremove(NmIter first_n, NmIter last_n, RmvIter first_r, RmvIter last_r)
{
    auto left_it = first_r;
    auto right_it = first_r;
    int cnt = 0;

    for (; right_it != last_r; ++right_it) {
        auto it = first_n;
        while (it != last_n && *it != cnt) { ++it; }
        if (it == last_n) { *left_it++ = std::move(*right_it); }
        ++cnt;
    }

    return left_it;
}
