#include <functional>

template <class T>
T myfilter(const T &a, std::function<bool(typename T::value_type)> f)
{
    T res;
    for (auto val : a)
    {
        if (f(val))
        {
            res.insert(res.end(), val);
        }
    }

    return res;
}
