export module reading;

import std;

export constexpr int not_a_reading = -7777;
export constexpr int not_a_month = -1;
export constexpr int implausible_min = -200;
export constexpr int implausible_max = 200;

export std::vector<std::string> month_input_tbl = {
	"-not a month-",
	"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};

export std::vector<std::string> month_print_tbl = {
	"-not a month-",
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
};

export struct Day {
	std::vector<double> hour = std::vector<double>(24, not_a_reading);
};

export struct Month {
	int month = not_a_month;
	std::vector<Day> day = std::vector<Day>(32);
};

export struct Year {
	int year;
	std::vector<Month> month = std::vector<Month>(12);
};

export struct Reading {
	int day;
	int hour;
	double temperature;
};

export void end_of_loop(std::istream& ist, char term, const std::string& message);
export int month_to_int(const std::string& s);
export std::string int_to_month(int i);
bool is_valid(const Reading& r);
std::istream& operator>>(std::istream& is, Reading& r);
std::istream& operator>>(std::istream& is, Month& m);
export std::istream& operator>>(std::istream& is, Year& y);
export void print_year(std::ostream& os, const Year& y);

void end_of_loop(std::istream& ist, char term, const std::string& message)
{
	if (ist.fail()) {
		ist.clear();
		char ch = 0;
		if (ist >> ch && ch == term)
			return;
		throw std::runtime_error{message};
	}
}

int month_to_int(const std::string& s)
{
	for (int i = 1; i < 13; ++i)
		if (month_input_tbl[i] == s)
			return i;
	return 0;
}

std::string int_to_month(int i)
{
	if (i < 1 || 13 <= i)
		throw std::runtime_error("bad month index");
	return month_print_tbl[i];
}

bool is_valid(const Reading& r)
{
	if (r.day < 1 || 31 < r.day)
		return false;
	if (r.hour < 0 || 23 < r.hour)
		return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

std::istream& operator>>(std::istream& is, Reading& r)
{
	char ch1;
	if (is >> ch1 && ch1 != '(') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}
	char ch2;
	if ((is >> r.day >> r.hour >> r.temperature >> ch2) && ch2 != ')')
		throw std::runtime_error{"bad reading"};
	return is;
}

std::istream& operator>>(std::istream& is, Month& m)
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}
	std::string month_marker;
	std::string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month")
		throw std::runtime_error{"bad start of month"};
	m.month = month_to_int(mm);

	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		} else
			++invalids;
	}
	if (invalids)
		throw std::runtime_error{std::format("invalid readings in month {}", invalids)};
	if (duplicates)
		throw std::runtime_error{std::format("duplicate readings in month {}", duplicates)};
	end_of_loop(is, '}', "bad end of month");
	return is;
}

std::istream& operator>>(std::istream& is, Year& y)
{
	char ch = 0;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}
	std::string year_marker;
	int yy = -1;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		throw std::runtime_error{"bad start of year"};
	y.year = yy;

	while (true) {
		Month m;
		if (!(is >> m))
			break;
		y.month[m.month-1] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

void print_year(std::ostream& os, const Year& y)
{
	for (const Month& m : y.month) {
		if (m.month == not_a_month)
			continue;
		for (size_t i = 1; i < m.day.size(); ++i) {
			for (size_t j = 1; j < m.day[i].hour.size(); ++j) {
				if (m.day[i].hour[j] == not_a_reading)
					continue;
				os << std::format("{:02} {:9} {:04} {:02} {:.2f}\n",
								  i, //day
								  month_print_tbl[m.month], //month
								  y.year, //year
								  j, //hour
								  m.day[i].hour[j] //temp
				);
			}
		}
	}
}
