import std;

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream& os, const Reading& r)
{
	return os << r.hour << '\t' << std::fixed << std::setprecision(2) << r.temperature;
}

std::istream& operator>>(std::istream& is, Reading& r)
{
	int hour;
	double temp;
	if (is >> hour >> temp) {
		if (hour < 0 || hour > 23) {
			is.clear(std::ios::failbit);
			return is;
		}
		r = Reading{hour, temp};
	}
	return is;
}

bool operator<(const Reading& lhs, const Reading& rhs)
{
	return lhs.hour < rhs.hour;
}

bool compare_temp(const Reading& lhs, const Reading& rhs)
{
	return lhs.temperature < rhs.temperature;
}

int main()
{
	try {
		const std::string filename = "raw_temps.txt";
		std::ifstream ifs(filename);
		if (!ifs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};

		std::vector<Reading> temps;
		for (Reading r; ifs >> r;)
			temps.push_back(r);

		if (temps.size() == 0)
			throw std::runtime_error("failed to read any readings");

		std::sort(temps.begin(), temps.end(), compare_temp);
		double mean = 0;
		for (const Reading& r: temps)
			mean += r.temperature;
		mean /= temps.size();

		const size_t& mid = temps.size()/2;
		double median = temps.size()%2 == 0 ?
			(temps[mid].temperature + temps[mid-1].temperature)/2 :
			temps[mid].temperature;

		std::cout << std::fixed << std::setprecision(2) <<
			"mean:\t" << mean << '\n' <<
			"median:\t" << median << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "exception \n";
		return 2;
	}
}
