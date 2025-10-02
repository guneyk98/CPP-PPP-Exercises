export module Reading;

import std;

export struct Reading {
	int hour;
	double temperature;
	char unit;
};

export std::ostream& operator<<(std::ostream& os, const Reading& r)
{
	return os << r.hour << '\t' << std::fixed << std::setprecision(2) << r.temperature << r.unit;
}

export std::istream& operator>>(std::istream& is, Reading& r)
{
	int hour; double temp; char unit;
	if (is >> hour >> temp >> unit) {
		if (hour < 0 || hour > 23 ||
			!(unit == 'C' || unit == 'F' || unit == 'c' || unit == 'f')) {
			is.clear(std::ios::failbit);
			return is;
		}
		r = Reading{hour, temp,
			static_cast<char>(std::tolower(static_cast<unsigned char>(unit)))};
	}
	return is;
}

export bool operator<(const Reading& lhs, const Reading& rhs)
{
	return lhs.hour < rhs.hour;
}

export bool compare_temp(const Reading& lhs, const Reading& rhs)
{
	return lhs.temperature < rhs.temperature;
}

export double ctof(double c)
{
	if (c < -273.25)
		throw std::runtime_error(std::to_string(c)+"C is below absolute zero");
	const double f = 1.8*c + 32.0;
	return f;
}

export double ftoc(double f)
{
	if (f < -459.67)
		throw std::runtime_error(std::to_string(f)+"F is below absolute zero");
	const double c = (f-32.0) * (5.0/9.0);
	return c;
}
