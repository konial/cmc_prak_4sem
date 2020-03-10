#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace numbers
{
	class complex {
		double re_{}, im_{};
	public:
		complex() {};
		complex(double, double);
		explicit complex(std::string);

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
	complex::complex(std::string str)
	{
		std::istringstream sin(str);
		char rubbish;
		sin >> rubbish >> re_ >> rubbish >> im_;
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

		auto lambda_pushVal = [&st, &str]()
		{
			complex z1(str);
			st = st << z1;
		};
		auto lambda_pushZ = [&st, z]() { st = st << z; };
		auto lambda_plus = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			complex z2 = +st;
			st = ~st;
			st = st << z2 + z1;
		};
		auto lambda_minus = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			complex z2 = +st;
			st = ~st;
			st = st << z2 - z1;
		};
		auto lambda_mul = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			complex z2 = +st;
			st = ~st;
			st = st << z2 * z1;
		};
		auto lambda_div = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			complex z2 = +st;
			st = ~st;
			st = st << z2 / z1;
		};
		auto lambda_pushLast = [&st]()
		{
			complex z1 = +st;
			st = st << z1;
		};
		auto lambda_pop = [&st]() { st = ~st; };
		auto lambda_pushLastInv = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			st = st << ~z1;
		};
		auto lambda_pushLastNeg = [&st]()
		{
			complex z1 = +st;
			st = ~st;
			st = st << -z1;
		};

		std::map< char, std::function<void()> > calc;
		calc.insert(std::pair< char, std::function<void()> >('(', lambda_pushVal));
		calc.insert(std::pair< char, std::function<void()> >('z', lambda_pushZ));
		calc.insert(std::pair< char, std::function<void()> >('+', lambda_plus));
		calc.insert(std::pair< char, std::function<void()> >('-', lambda_minus));
		calc.insert(std::pair< char, std::function<void()> >('*', lambda_mul));
		calc.insert(std::pair< char, std::function<void()> >('/', lambda_div));
		calc.insert(std::pair< char, std::function<void()> >('!', lambda_pushLast));
		calc.insert(std::pair< char, std::function<void()> >(';', lambda_pop));
		calc.insert(std::pair< char, std::function<void()> >('~', lambda_pushLastInv));
		calc.insert(std::pair< char, std::function<void()> >('#', lambda_pushLastNeg));

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
	numbers::complex C(argv[1]);
	double R;
	getFromString(argv[2], R);
	int N;
	getFromString(argv[3], N);

	std::vector<std::string> args;
	for (int i = 4; i < argc; ++i)
	{
		args.push_back(argv[i]);
	}

	const double PI = 3.14159265358979323846;
	numbers::complex I = 0;
	double prevAngle = 0;
	numbers::complex prevZ = C + numbers::complex(R, 0);

	for (int i = 1; i <= N; ++i)
	{
		double angle = 2.0 * PI * i / N;
		numbers::complex z = C + numbers::complex(R * cos(angle), R * sin(angle));
		double arg = (angle + prevAngle) / 2.0;
		numbers::complex val = C + numbers::complex(R * cos(arg), R * sin(arg));
		I += numbers::eval(args, val) * (z - prevZ);
		prevAngle = angle;
		prevZ = z;
	}

	std::cout << I.to_string() << std::endl;

	return 0;
}
