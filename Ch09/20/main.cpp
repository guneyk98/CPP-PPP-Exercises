import std;
import reading;

int main()
{
	try {
		std::string iname = "input.txt";
		std::ifstream ifs{iname};
		if (!ifs)
			throw std::runtime_error{std::format("can't open input file {}", iname)};
		ifs.exceptions(ifs.exceptions()|std::ios::badbit);

		std::string oname = "output.txt";
		std::ofstream ofs{oname};
		if (!ofs)
			throw std::runtime_error{std::format("can't open output file {}", oname)};

		std::vector<Year> ys;
		while (true) {
			Year y;
			if (!(ifs >> y))
				break;
			ys.push_back(y);
		}
		std::cout << "read " << ys.size() << " years of readings\n";

		for (Year& y : ys)
			print_year(ofs, y);
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
