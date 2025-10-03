import std;

int main()
{
	try {
		std::cout << "Enter the name of the first file: ";
		std::string iname1;
		std::cin >> iname1;
		std::ifstream ifs1 {iname1};
		if (!ifs1)
			throw std::runtime_error{std::format("can't open input file {}", iname1)};
		
		std::cout << "Enter the name of the second file: ";
		std::string iname2;
		if (iname1 == iname2)
			throw std::exception{"files names cannot be the same"};
		std::cin >> iname2;
		std::ifstream ifs2{iname2};
		if (!ifs2)
			throw std::runtime_error{std::format("can't open input file {}", iname2)};

		std::string oname = "output.txt";
		std::ofstream ofs{oname};
		if (!ofs)
			throw std::runtime_error{std::format("can't open output file {}", oname)};

		for (std::string line; std::getline(ifs1, line); )
			ofs << line << '\n';
		for (std::string line; std::getline(ifs2, line); )
			ofs << line << '\n';
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
