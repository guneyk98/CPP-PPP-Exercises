import std;

int main()
{
	try {
		const std::string filename = "input.txt";
		std::ifstream ifs(filename);
		if (!ifs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};

		std::vector<double> nums;
		for (double n; ifs >> n;)
			nums.push_back(n);

		for (size_t i = 0; i < nums.size(); ++i) {
			if (i && i%4 == 0)
				std::cout << '\n';
			std::cout << std::format("{:20.8e}", nums[i]);
		}
		std::cout << '\n';
			
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
