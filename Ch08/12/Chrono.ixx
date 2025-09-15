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

//first day_of_year of each month
constexpr int month_start_normal[12] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
constexpr int month_start_leap[12] = {1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336};

//1 Jan 1970
constexpr int epoch_y = 1970;
constexpr long days_y0_to_epoch = 1L + 365L*epoch_y + epoch_y/4L - epoch_y/100L + epoch_y/400L;
constexpr Day first_day{Day::thu};

struct Year {
	int y;
};

class Date {
public:
	Date(Year y, Month m, int d);
	Date(long days) : d{days} {}

	Year year() const;
	Month month() const;
	int day() const;

	long days() const { return d; }

	void add_year(int n);
	void add_month(int n);
	void add_day(int n);
private:
	long d;
};

bool is_date(Year y, Month m, int d);
int days_in_month(Month m, Year y);
bool leapyear(Year y);
Day day_of_week(const Date& d);
int day_of_year(const Date& d);
int leapdays_since_first(const Date& d);
Date next_workday(const Date& d);
int week_of_year(const Date& d);
//outputs day of year (1 jan -> doy = 1) and the year
void breakdown_days(long days, int& year, int& day_of_year);

std::ostream& operator<<(std::ostream& os, const Date& d);
std::ostream& operator<<(std::ostream& os, const Day& d);
std::ostream& operator<<(std::ostream& os, const Month& m);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);

//Implementation

Date::Date(Year yy, Month mm, int dd)
{
	if (!is_date(yy, mm, dd))
		throw std::runtime_error{"Invalid date"};

	d = 0;
	add_year(yy.y-epoch_y);
	add_month(static_cast<int>(mm)-1);
	add_day(dd-1);
}

Year Date::year() const
{
	int y, doy;
	breakdown_days(d, y, doy);
	return Year{y};
}

Month Date::month() const
{
	int y, doy;
	breakdown_days(d, y, doy);

	const int (&month_starts)[12] = leapyear(Year{y}) ? month_start_leap : month_start_normal;

	// Find month via binary search (constant time for 12 entries)
	int m = std::upper_bound(month_starts, month_starts+12, doy) - month_starts;
	return Month{m};
}

int Date::day() const
{
	int y, doy;
	breakdown_days(d, y, doy);
	bool is_leap = leapyear(Year{y});
	auto const& month_starts = is_leap ? month_start_leap : month_start_normal;

	int m = std::upper_bound(month_starts, month_starts + 12, doy) - month_starts;
	return 1 + doy - month_starts[m - 1];
}

void Date::add_day(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_day() doesn't take in negative values"};
	d += n;
}

void Date::add_month(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_month() doesn't take in negative values"};

	add_year(n/12);
	n %= 12;
	for (int i = 0; i < n; ++i)
		d += days_in_month(month(), year());
}

void Date::add_year(int n)
{
	if (n < 0)
		throw std::runtime_error{"add_year() doesn't take in negative values"};
	
	int y, doy;
	breakdown_days(d, y, doy);

	const int new_year = y+n;
	//0000-01-01 -> yyyy-01-01 (Start of year)
	const int leapdays_since_y0 = (new_year-1)/4 - (new_year-1)/100 + (new_year-1)/400;
	const long days_since_y0 = 365L * new_year + leapdays_since_y0;

	d = days_since_y0 - days_y0_to_epoch + doy;
	if (leapyear(Year{y}) && !leapyear(Year{new_year}) && doy > 60)
		--d;
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

Day day_of_week(const Date& d)
{
	const int n = d.days()%7;
	return Day{(static_cast<int>(first_day)+n)%7};
}

int day_of_year(const Date& d)
{
	int y, doy;
	breakdown_days(d.days(), y, doy);
	return doy;
}

int leapdays_since_first(const Date& d)
{
	int n = (d.year().y/4 - d.year().y/100 +d.year().y/400) -
		(epoch_y/4 - epoch_y/100 + epoch_y/400);

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

void breakdown_days(long days, int& year, int& day_of_year)
{
	const long days_since_y0 = days + days_y0_to_epoch;

	//days within 400, 100 and 4-year cycles
	constexpr long days_400y = 365*400 + 400/4 - 400/100 + 400/400;
	constexpr long days_100y = 365*100 + 100/4 - 100/100;
	constexpr long days_4y = 365*4 + 4/4;

	const long n400y = days_since_y0/days_400y; //number of full 400-year cycles
	year = static_cast<int>(n400y*400);
	long day_of_cycle = days_since_y0 - n400y*days_400y; //days within last 400-year cycle

	const long n100y = day_of_cycle/days_100y;
	year += static_cast<int>(n100y*100);
	day_of_cycle -= n100y*days_100y;

	const long n4y = day_of_cycle/days_4y;
	year += static_cast<int>(n4y*4);
	day_of_cycle -= n4y*days_4y;

	//check if the first year of the 4-year cycle is a leapyear
	if (leapyear(Year{year}) && day_of_cycle >= 365) {
		if (day_of_cycle == 365) {
			day_of_year = static_cast<int>(day_of_cycle);
			return;
		}
		++year;
		day_of_cycle -= 366;
	}
	const long n1y = day_of_cycle/365;
	year += static_cast<int>(n1y);
	day_of_cycle -= n1y * 365;

	//add one so first day = 1
	day_of_year = 1 + static_cast<int>(day_of_cycle);
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
	return lhs.days() == rhs.days();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs==rhs);
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return lhs.days() < rhs.days();
}
}
