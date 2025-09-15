export module Rational;

import std;

export class Rational {
public:
	Rational(int numerator, int denominator);

	int numer() const { return n; }
	int denom() const { return d; }

	operator double() const { return double(n)/double(d); }
private:
	int n, d;

	void simplify();
};

export Rational operator+(const Rational& lhs, const Rational& rhs);
export Rational operator-(const Rational& lhs, const Rational& rhs);
export Rational operator*(const Rational& lhs, const Rational& rhs);
export Rational operator/(const Rational& lhs, const Rational& rhs);
export bool operator==(const Rational& lhs, const Rational& rhs);
export std::ostream& operator<<(std::ostream& os, const Rational& r);

//helper functions for detecting overflow/underflow
int safe_add(int a, int b);
int safe_sub(int a, int b);
int safe_mul(int a, int b);

//greatest common factor
int gcf(int a, int b);

//Implementation

Rational::Rational(int numer, int denom) : n{numer}, d{denom}
{
	if (d == 0)
		throw std::runtime_error("denominator cannot be 0");

	if (n == 0) {
		d = 1; //to avoid unnecessary overflow
		return;
	}

	//Keep the denominator positive
	if (d < 0) {
		if (d == std::numeric_limits<int>::min() || n == std::numeric_limits<int>::min())
			throw std::runtime_error("can't allocate INT_MIN to denominator or numerator, if the denominator is negative");

		n *= -1;
		d *= -1;
	}
	simplify();
}

void Rational::simplify()
{
	const int g = gcf(std::abs(n), d);
	n /= g;
	d /= g;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	if (lhs.denom() == rhs.denom()) {
		return Rational{safe_add(lhs.numer(), rhs.numer()), lhs.denom()};
	}
	const int denom = safe_mul(lhs.denom(), rhs.denom());
	const int numer = safe_add(safe_mul(lhs.numer(), rhs.denom()), safe_mul(rhs.numer(), lhs.denom()));
	return Rational{numer, denom};
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	if (lhs.denom() == rhs.denom()) {
		return Rational{safe_sub(lhs.numer(), rhs.numer()), lhs.denom()};
	}
	const int denom = safe_mul(lhs.denom(), rhs.denom());
	const int numer = safe_sub(safe_mul(lhs.numer(), rhs.denom()), safe_mul(rhs.numer(), lhs.denom()));
	return Rational{numer, denom};
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	const int numer = safe_mul(lhs.numer(), rhs.numer());
	const int denom = safe_mul(lhs.denom(), rhs.denom());
	return Rational{numer, denom};
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	if (rhs.numer() == 0)
		throw std::runtime_error("divide by zero");
	const int numer = safe_mul(lhs.numer(), rhs.denom());
	const int denom = safe_mul(lhs.denom(), rhs.numer());
	return Rational{numer, denom};
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
	//both objects should always be in simplified form, due to simplify() call in constructor
	return lhs.numer() == rhs.numer() && lhs.denom() == rhs.denom();
}

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
	return os << r.numer() << '/' << r.denom();
}

int safe_add(int a, int b)
{
	if (b > 0 && (a > std::numeric_limits<int>::max()-b))
		throw std::overflow_error("integer overflow in addition");
	if (b < 0 && (a < std::numeric_limits<int>::min()-b))
		throw std::underflow_error("integer underflow in addition");
	return a+b;
}

int safe_sub(int a, int b)
{
	if (b < 0 && (a > std::numeric_limits<int>::max()+b))
		throw std::overflow_error("integer overflow in subtraction");
	if (b > 0 && (a < std::numeric_limits<int>::min()+b))
		throw std::underflow_error("integer underflow in subtraction");
	return a-b;
}

int safe_mul(int a, int b)
{
	if (a > 0) {
		if (b > 0) {
			if (a > std::numeric_limits<int>::max()/b)
				throw std::overflow_error("integer overflow in multiplication");
		} else {
			if (b < std::numeric_limits<int>::min()/a)
				throw std::underflow_error("integer underflow in multiplication");
		}
	} else {
		if (b > 0) {
			if (a < std::numeric_limits<int>::min()/b)
				throw std::underflow_error("integer underflow in multiplication");
		} else {
			if (a != 0 && b < std::numeric_limits<int>::max()/a)
				throw std::overflow_error("integer overflow in multiplication");
		}
	}
	return a*b;
}

int gcf(int a, int b)
{
	int remainder;
    while (b > 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
