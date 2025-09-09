export module Chrono;

import std;

export namespace Chrono {

enum class Day {
	mon, tue, wed, thu, fri, sat, sun
};
std::array<const char*, 7> day_tbl{
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
std::array<const char*, 12> month_tbl{
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"};

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

//First day of Gregorian calendar: Friday, October 15, 1582
const Date first_date{Year{1582}, Month::oct, 15};
const Day first_day{Day::fri};

bool is_date(Year y, Month m, int d);
int days_in_month(Month m, Year y);
bool leapyear(Year y);
int days_since_first(const Date& d);
Day day_of_week(const Date& d);
int day_of_year(const Date& d);
int leapdays_since_first(const Date& d);
Date next_workday(const Date& d);
int week_of_year(const Date& d);

std::ostream& operator<<(std::ostream& os, const Date& d);
std::ostream& operator<<(std::ostream& os, const Day& d);
std::ostream& operator<<(std::ostream& os, const Month& m);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);

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

	while (n+d > days_in_month(m, y)) {
		n -= days_in_month(m, y);
		add_month(1);
	}
	d += n;
}

void Date::add_month(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_month() doesn't take in negative values"};

	while (n+static_cast<int>(m) > 12) {
		n -= 12;
		add_year(1);
	}
	m = Month{1 + (n+static_cast<int>(m)-1)%12};
}

void Date::add_year(int n)
{
	if (m == Month::feb && leapyear(y)) {
		m = Month::mar;
		d = 1;
	}
	y.y += n;
}

bool is_date(Year y, Month m, int d)
{
	return d>0 && d<=days_in_month(m, y);
}

int days_in_month(Month m, Year y)
{
	switch (m) {
	case Month::feb:
		return leapyear(y) ? 29 : 28;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		return 30;
	default:
		return 31;
	}
}

bool leapyear(Year y)
{
	return  (y.y%4 == 0 && y.y%100 != 0) || y.y%400 == 0;
}

int days_since_first(const Date& d)
{
	if (d < first_date)
		throw std::exception{"Can't handle days before Friday, October 15, 1582"};

	const int years = d.year().y - first_date.year().y;
	int days = day_of_year(d) - day_of_year(first_date);

	if (leapyear(d.year()) && (d.month() > Month::feb))
		--days;

	return 365*years + days + leapdays_since_first(d);
}

Day day_of_week(const Date& d)
{
	const int n = days_since_first(d)%7;
	return Day{(static_cast<int>(first_day)+n)%7};
}

int day_of_year(const Date& d)
{
	int res = 0;
	switch (d.month()) {
	case Month::dec: res += 30; [[fallthrough]];
	case Month::nov: res += 31; [[fallthrough]];
	case Month::oct: res += 30; [[fallthrough]];
	case Month::sep: res += 31; [[fallthrough]];
	case Month::aug: res += 31; [[fallthrough]];
	case Month::jul: res += 30; [[fallthrough]];
	case Month::jun: res += 31; [[fallthrough]];
	case Month::may: res += 30; [[fallthrough]];
	case Month::apr: res += 31; [[fallthrough]];
	case Month::mar: res += leapyear(d.year()) ? 29 : 28; [[fallthrough]];
	case Month::feb: res += 31; [[fallthrough]];
	}
	res += d.day();
	return res;
}

int leapdays_since_first(const Date& d)
{
	int n = (d.year().y/4 - d.year().y/100 +d.year().y/400) -
		(first_date.year().y/4 - first_date.year().y/100 + first_date.year().y/400);

	if (leapyear(d.year()) && (d.month() < Month::mar))
		--n;
	return n;
}

Date next_workday(const Date& d)
{
	const Day day = day_of_week(d);
	Date res = d;
	switch (day) {
	case Day::fri: res.add_day(3); break;
	case Day::sat: res.add_day(2); break;
	default: res.add_day(1); break;
	}
	return res;
}

int week_of_year(const Date& d)
{
	const Day first = day_of_week({d.year(), Month::jan, 1});
	return 1 + (static_cast<int>(first) + day_of_year(d)-1)/7;
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << d.year().y << '/' << static_cast<int>(d.month()) << '/' << d.day();
}

std::ostream& operator<<(std::ostream& os, const Day& d)
{
	return os << day_tbl[static_cast<int>(d)];
}

std::ostream& operator<<(std::ostream& os, const Month& m)
{
	return os << month_tbl[static_cast<int>(m)];
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

bool operator<(const Date& lhs, const Date& rhs)
{
	return lhs.year().y < rhs.year().y ||
		(lhs.year().y == rhs.year().y && lhs.month() < rhs.month()) ||
		(lhs.year().y == rhs.year().y && lhs.month() == rhs.month() && lhs.day() < rhs.day());;
}
}
