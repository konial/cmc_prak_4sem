#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <stdlib.h>
 
namespace numbers
{
    class complex {
        double re_{}, im_{};
    public:
        complex() {};
        complex(double, double);
        explicit complex(const std::string&);
 
        double re() const;
        double im() const;
 
        double abs2() const;
        double abs() const;
 
        std::string to_string() const;
 
        const complex& operator+=(const complex&);
        const complex& operator-=(const complex&);
        const complex& operator*=(const complex&);
        const complex& operator/=(const complex&);
 
        complex operator~() const;
        complex operator-() const;
    };
 
    complex::complex(double re, double im = 0) : re_(re), im_(im) {};
    complex::complex(const std::string &str)
    {
        std::istringstream in(str);
        char rubbish;
        in >> rubbish >> re_ >> rubbish >> im_;
    }
 
    double complex::re() const { return re_; }
    double complex::im() const { return im_; }
 
    double complex::abs2() const { return re_ * re_ + im_ * im_; }
    double complex::abs() const { return sqrt(this->abs2()); }
 
    std::string complex::to_string() const
    {
        std::ostringstream sout;
        sout << std::setprecision(10) << '(' << re_ << ',' << im_ << ')';
        return sout.str();
    }
 
    const complex& complex::operator+=(const complex &z)
    {
        this->re_ += z.re_;
        this->im_ += z.im_;
        return *this;
    }
    const complex& complex::operator-=(const complex &z)
    {
        this->re_ -= z.re_;
        this->im_ -= z.im_;
        return *this;
    }
    const complex& complex::operator*=(const complex &z)
    {
        double pre_ = this->re_ * z.re_ - this->im_ * z.im_;
        double pim_ = this->re_ * z.im_ + this->im_ * z.re_;
        this->re_ = pre_;
        this->im_ = pim_;
        return *this;
    }
    const complex& complex::operator/=(const complex &z)
    {
        double pre_ = (this->re_ * z.re_ + this->im_ * z.im_)
            / (z.re_ * z.re_ + z.im_ * z.im_);
        double pim_ = (this->im_ * z.re_ - this->re_ * z.im_)
            / (z.re_ * z.re_ + z.im_ * z.im_);
        this->re_ = pre_;
        this->im_ = pim_;
        return *this;
    }
    complex operator+(const complex &z1, const complex &z2)
    {
        return complex(z1) += z2;
    }
    complex operator-(const complex &z1, const complex &z2)
    {
        return complex(z1) -= z2;
    }
    complex operator*(const complex &z1, const complex &z2)
    {
        return complex(z1) *= z2;
    }
    complex operator/(const complex &z1, const complex &z2)
    {
        return complex(z1) /= z2;
    }
    complex complex::operator~() const
    {
        return complex(this->re_, -this->im_);
    }
    complex complex::operator-() const
    {
        return complex(-this->re_, -this->im_);
    }
 
    class complex_stack {
        complex *top;
        size_t st_size{};
        size_t val_count{};
    public:
        complex_stack(size_t);
        complex_stack(const complex_stack&);
        ~complex_stack();
 
        size_t size() const;
        void swap(complex_stack&) noexcept;
        complex_stack& operator=(const complex_stack&);
        const complex operator[](const size_t) const;
        complex_stack operator<<(const complex) const;
        complex operator+() const;
        complex_stack operator~() const;
    };
 
    complex_stack::complex_stack(size_t count = 0) : val_count(count) {
        st_size = (count == 0 ? 1 : count);
        top = new complex[st_size];
    }
    complex_stack::complex_stack(const complex_stack &st) : st_size(st.st_size), val_count(st.val_count)
    {
        top = new complex[(int)st_size];
        for (size_t i = 0; i < val_count; ++i)
        {
            top[i] = st.top[i];
        }
    }
    complex_stack::~complex_stack()
    {
        delete[] top;
    }
 
    size_t complex_stack::size() const { return val_count; }
    void complex_stack::swap(complex_stack &st) noexcept
    {
        std::swap(st_size, st.st_size);
        std::swap(val_count, st.val_count);
        std::swap(top, st.top);
    }
    complex_stack& complex_stack::operator=(const complex_stack &st)
    {
        complex_stack tmp(st);
        this->swap(tmp);
        return *this;
    }
    const complex complex_stack::operator[](const size_t i) const
    {
        return top[i];
    }
    complex_stack complex_stack::operator<<(const complex val) const
    {
        complex_stack new_st(*this);
        if (new_st.val_count + 1 > new_st.st_size)
        {
            new_st.st_size *= 2;
            delete[] new_st.top;
            new_st.top = new complex[new_st.st_size];
            for (size_t i = 0; i < new_st.val_count; ++i)
            {
                new_st.top[i] = this->top[i];
            }
        }
        ++new_st.val_count;
        new_st.top[new_st.val_count - 1] = val;
        return new_st;
    }
    complex complex_stack::operator+() const
    {
        return (*this)[this->val_count - 1];
    }
    complex_stack complex_stack::operator~() const
    {
        complex_stack new_st(*this);
        new_st.val_count--;
        delete[] new_st.top;
        new_st.top = new complex[st_size];
        for (size_t i = 0; i < new_st.val_count; ++i)
        {
            new_st.top[i] = this->top[i];
        }
        return new_st;
    }
 
    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        complex_stack st;
        std::string str;
 
        std::map< char, std::function<void()> > calc
        {
            {'(', [&st, &str]()
                {
                    complex z1(str);
                    st = st << z1;
                }
            },
            {'z', [&st, z]()
                {
                    st = st << z;
                }
            },
            {'+', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    complex z2 = +st;
                    st = ~st;
                    st = st << z2 + z1;
                }
            },
            {'-', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    complex z2 = +st;
                    st = ~st;
                    st = st << z2 - z1;
                }
            },
            {'*', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    complex z2 = +st;
                    st = ~st;
                    st = st << z2 * z1;
                }
            },
            {'/', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    complex z2 = +st;
                    st = ~st;
                    st = st << z2 / z1;
                }
            },
            {'!', [&st]()
                {
                    complex z1 = +st;
                    st = st << z1;
                }
            },
            {';', [&st]()
                {
                    st = ~st;
                }
            },
            {'~', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    st = st << ~z1;
                }
            },
            {'#', [&st]()
                {
                    complex z1 = +st;
                    st = ~st;
                    st = st << -z1;
                }
            }
        };
 
        for (size_t i = 0; i < args.size(); ++i)
        {
            str = args[i];
            calc[str[0]]();
        }
 
        return +st;
    }
}
 
template < typename T >
void getFromString(const char* str, T& val)
{
    std::istringstream in(str);
    in >> val;
}
 
int main(int argc, char **argv)
{
    numbers::complex c(argv[1]);
    double r;
    getFromString(argv[2], r);
    int n;
    getFromString(argv[3], n);
 
    std::vector<std::string> args;
    for (int i = 4; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
 
    numbers::complex ans = 0;
    double prevAngle = 0;
    numbers::complex prevZ = c + numbers::complex(r, 0);
 
    for (int i = 1; i <= n; ++i)
    {
        double angle = 2.0 * M_PI * i / n;
        numbers::complex z = c + numbers::complex(r * cos(angle), r * sin(angle));
        double arg = (angle + prevAngle) / 2.0;
        numbers::complex val = c + numbers::complex(r * cos(arg), r * sin(arg));
        ans += numbers::eval(args, val) * (z - prevZ);
        prevAngle = angle;
        prevZ = z;
    }
 
    std::cout << ans.to_string() << std::endl;
 
    return 0;
}
