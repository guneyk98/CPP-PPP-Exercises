export module Money;

import std;

export enum class Currency {
	USD, EUR, GBP
};

constexpr std::array curr_symbol{
	"USD", "EUR", "GBP"
};

constexpr std::array<std::array<double, 3>, 3> curr_tbl{{
	{{1.00, 0.84, 0.73}}, //USD to x
	{{1.19, 1.00, 0.87}}, //EUR to x
	{{1.36, 1.15, 1.00}}  //GBP to x
}};

constexpr std::array<double, 3> a = {3, 4, 3 };

export class Money {
public:
	Money(Currency c) : c{c}, m{0} {}
	Money(Currency c, long m) : c{c}, m{m} {}
	Money(Currency c, long dollars, int cents);
	Money(Currency c, double f);

	long dollars() const { return m/100; }
	int cents() const { return static_cast<int>(std::abs(m)%100); }
	int money() const { return m; }
	Currency currency() const { return c; }

private:
	long m;
	Currency c;
};

export Money operator+(const Money& lhs, const Money& rhs);
export Money operator-(const Money& lhs, const Money& rhs);
export bool operator==(const Money& lhs, const Money& rhs);
export bool operator!=(const Money& lhs, const Money& rhs);
export std::ostream& operator<<(std::ostream& os, const Money& r);

bool can_represent_as_long(double value);

//helper functions for detecting overflow/underflow
long safe_add(long a, long b);
long safe_sub(long a, long b);

//Implementation

Money::Money(Currency c, long dollars, int cents) : c{c}
{
	if (cents < 0 || cents >= 100)
		throw std::runtime_error{"cents input is out of bounds"};

	if (dollars > 0 && dollars > (std::numeric_limits<long>::max()-cents)/100)
		throw std::overflow_error("Money amount overflows");

	if (dollars < 0 && dollars < std::numeric_limits<long>::min()/100)
		throw std::underflow_error("Money amount underflows");

	m = 100*dollars + cents;
}

Money::Money(Currency c, double f) : c{c}
{
	f *= 100;
	if (!can_represent_as_long(f))
		throw std::runtime_error("Money floating-point value is not exactly representable as a long int");

	m = static_cast<long>(f);
}

Money operator+(const Money& lhs, const Money& rhs)
{
	//convert to lhs currency
	const double rate = curr_tbl[static_cast<int>(rhs.currency())][static_cast<int>(lhs.currency())];
	const long rhs_m = std::lround(rate * double(rhs.money()));
	return Money{lhs.currency(), safe_add(lhs.money(), rhs_m)};
}

Money operator-(const Money& lhs, const Money& rhs)
{
	//convert to lhs currency
	const double rate = curr_tbl[static_cast<int>(rhs.currency())][static_cast<int>(lhs.currency())];
	const long rhs_m = std::lround(rate * double(rhs.money()));
	return Money{lhs.currency(), safe_sub(lhs.money(), rhs_m)};
}

bool operator==(const Money& lhs, const Money& rhs)
{
	//convert to lhs currency
	const double conv_rate = curr_tbl[static_cast<int>(rhs.currency())][static_cast<int>(lhs.currency())];
	return lhs.money() ==  std::lround(conv_rate * rhs.money());
}

bool operator!=(const Money& lhs, const Money& rhs)
{
	return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& os, const Money& r)
{
	return os << curr_symbol[static_cast<int>(r.currency())] << r.dollars() << '.' << std::format("{:0>2}", r.cents());
}

bool can_represent_as_long(double value)
{
	//check range
	if (value < static_cast<double>(std::numeric_limits<long>::min()) ||
		value > static_cast<double>(std::numeric_limits<long>::max())) {
		return false;
	}
	//check if integer
	if (std::floor(value) != value) {
		return false;
	}
	return true;
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
