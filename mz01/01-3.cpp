class Sub
{
    long long int sub;
public:
    Sub(long long int a) : sub(a) {}
    Sub(Sub s1, Sub s2) : sub(s1.value() - s2.value()) {}
    long long int value() const { return sub; }
};
