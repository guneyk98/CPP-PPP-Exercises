export module Money;

import std;

export class Money {
public:
	Money() : m{0} {}
	Money(long dollars, int cents);
	Money(long m) : m{m} {}

	long dollars() const { return m/100; }
	int cents() const { return static_cast<int>(std::abs(m)%100); }
	int money() const { return m; }

private:
	long m;
};

export Money operator+(const Money& lhs, const Money& rhs);
export Money operator-(const Money& lhs, const Money& rhs);
export bool operator==(const Money& lhs, const Money& rhs);
export bool operator!=(const Money& lhs, const Money& rhs);
export std::ostream& operator<<(std::ostream& os, const Money& r);

//helper functions for detecting overflow/underflow
long safe_add(long a, long b);
long safe_sub(long a, long b);

//Implementation

Money::Money(long dollars, int cents)
{
	if (cents < 0 || cents >= 100)
		throw std::runtime_error{"cents input is out of bounds"};

	if (dollars > 0 && dollars > (std::numeric_limits<long>::max()-cents)/100)
		throw std::overflow_error("Money amount overflows");

	if (dollars < 0 && dollars < std::numeric_limits<long>::min()/100)
		throw std::underflow_error("Money amount underflows");

	m = 100*dollars + cents;
}

Money operator+(const Money& lhs, const Money& rhs)
{
	return Money{safe_add(lhs.money(), rhs.money())};
}

Money operator-(const Money& lhs, const Money& rhs)
{
	return Money{safe_sub(lhs.money(), rhs.money())};
}

bool operator==(const Money& lhs, const Money& rhs)
{
	return lhs.money() == rhs.money();
}

bool operator!=(const Money& lhs, const Money& rhs)
{
	return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& os, const Money& r)
{
	return os << '$' << r.dollars() << '.' << std::format("{:0>2}", r.cents());
}

long safe_add(long a, long b)
{
	if (b > 0 && (a > std::numeric_limits<long>::max()-b))
		throw std::overflow_error("integer overflow in addition");
	if (b < 0 && (a < std::numeric_limits<long>::min()-b))
		throw std::underflow_error("integer underflow in addition");
	return a+b;
}

long safe_sub(long a, long b)
{
	if (b < 0 && (a > std::numeric_limits<long>::max()+b))
		throw std::overflow_error("integer overflow in subtraction");
	if (b > 0 && (a < std::numeric_limits<long>::min()+b))
		throw std::underflow_error("integer underflow in subtraction");
	return a-b;
}
