#include <functional>
#include <vector>

template <class Iter, class Func>
void myapply(Iter first, Iter last, Func f)
{
    while (first != last) {
        f(*first++);
    }
}

template <class Iter, class Predicate>
auto myfilter2(Iter first, Iter last, Predicate f)
{
    auto val = *first;
    std::vector<std::reference_wrapper<decltype(val)>> res;
    
    while (first != last) {
        if (f(*first)) {
            res.push_back(*first);
        }
        ++first;
    }

    return res;
}
