import std;
import Reading;

int main()
{
	try {
		const std::string filename = "raw_temps.txt";
		std::ifstream ifs(filename);
		if (!ifs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};

		std::vector<Reading> temps;
		for (Reading r; ifs >> r;) {
			if (r.unit == 'c' || r.unit == 'C') {
				r.temperature = ctof(r.temperature);
				r.unit = 'f';
			}
			temps.push_back(r);
		}

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
			"mean:\t" << mean << 'f' << " or " << ftoc(mean) << 'c' << '\n' <<
			"median:\t" << median << 'f' << " or " << ftoc(median) << 'c' << '\n';
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
