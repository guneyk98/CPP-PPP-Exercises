import std;

int main()
{
	try {
		const std::string filename = "input.txt";
		std::ifstream ifs(filename);
		if (!ifs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};
		
		int sum = 0;
		for (int n; ifs >> n;)
			sum += n;
		std::cout << "sum: " << sum << '\n';
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
