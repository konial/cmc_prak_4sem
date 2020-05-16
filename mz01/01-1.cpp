class Sum
{
    long long int sum;
public:
    Sum(long long int a, long long int b) : sum(a + b) {}
    Sum(Sum s, long long int c) : sum(s.get() + c) {}
    long long int get() const { return sum; }
};
