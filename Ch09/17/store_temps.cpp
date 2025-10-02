import std;

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream& os, const Reading& r)
{
	return os << r.hour << '\t' << std::fixed << std::setprecision(2) << r.temperature;
}

bool operator<(const Reading& lhs, const Reading& rhs)
{
	return lhs.hour < rhs.hour;
}

int main()
{
	try {
		const std::string filename = "raw_temps.txt";
		std::ofstream ofs(filename);
		if (!ofs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};

		constexpr double temp_mean = 15.0, temp_sd = 5.0;
		std::default_random_engine engine;
		std::uniform_int_distribution<int> dist_h(0, 23);
		std::normal_distribution<double> dist_t(temp_mean, temp_sd);

		std::vector<Reading> temps;
		for (size_t i = 0; i < 50; ++i)
			temps.push_back(Reading{dist_h(engine), dist_t(engine)});
		std::sort(temps.begin(), temps.end());

		for (const Reading& r : temps)
			ofs << r << '\n';
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
