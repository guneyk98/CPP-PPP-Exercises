import std;
import Reading;

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
		std::uniform_int_distribution<int> dist_u(0, 1);

		std::vector<Reading> temps;
		for (size_t i = 0; i < 50; ++i) {
			if (dist_u(engine))
				temps.push_back(Reading{dist_h(engine), dist_t(engine), 'c'});
			else
				temps.push_back(Reading{dist_h(engine), ctof(dist_t(engine)), 'f'});
		}
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
