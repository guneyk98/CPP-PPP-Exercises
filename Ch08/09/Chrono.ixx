export module Chrono;

import std;

export namespace Chrono {

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

struct Year {
	int y;
};

class Date {
public:
	Date(Year y, Month m, int d);

	Year year() const { return y; };
	Month month() const { return m; };
	int day() const { return d; }

	void add_year(int n);
	void add_month(int n);
	void add_day(int n);
private:
	Year y;
	Month m;
	int d;
};

bool is_date(Year y, Month m, int d);
int days_in_month(Month m);

std::ostream& operator<<(std::ostream& os, const Date& d);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

//Implementation

Date::Date(Year yy, Month mm, int dd) : y{yy}, m{mm}, d{dd}
{
	if (!is_date(yy, mm, dd))
		throw std::runtime_error{"Invalid date"};
}

void Date::add_day(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_day() doesn't take in negative values"};
	
	while (n+d > days_in_month(m)) {
		n -= days_in_month(m);
		add_month(1);
	}
	d += n;
}

void Date::add_month(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_month() doesn't take in negative values"};

	add_year((n+static_cast<int>(m)-1)/12);
	m = Month{1 + (n+static_cast<int>(m)-1)%12};

	//e.g. 2020/01/31 -> 2020/03/03
	if (d > days_in_month(m)) {
		d -= days_in_month(m);
		add_month(1);
	}
}

void Date::add_year(int n)
{
	y.y += n; //implement leap years in future exercise
}

bool is_date(Year y, Month m, int d)
{
	return d>0 && d<=days_in_month(m);
}

int days_in_month(Month m)
{
	switch (m) {
	case Month::feb:
		return 28; //implement leap years in future exercise
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		return 30;
	default:
		return 31;
	}
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << d.year().y << '/' << static_cast<int>(d.month()) << '/' << d.day();
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.year().y == rhs.year().y &&
		lhs.month()  == rhs.month() &&
		lhs.day() == rhs.day();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs==rhs);
}
}
