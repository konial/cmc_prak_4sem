template <class T>
typename T::value_type process(const T &a)
{
    typename T::value_type sum = typename T::value_type();
    typename T::const_iterator it = a.end();

    
    int count = a.size() * (a.size() < 5) + 5 * (a.size() >= 5);
    for (int i = 0; i < count; ++i) {
        if (i % 2) {
            --it;
        }
        else {
            sum += *--it;
        }
    }

    return sum;
}
