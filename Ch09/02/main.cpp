import std;

bool contains_word(const std::string& str, const std::string& word)
{
	std::istringstream is{str};
	for (std::string x; is >> x;)
		if (x == word)
			return true;
	return false;
}

int main()
{
	try {
		std::cout << "Enter a file name to open: ";
		std::string in_filename;
		if (!(std::cin >> in_filename))
			throw std::exception{"failed to read filename string"};

		std::ifstream ist{in_filename};
		if (!ist)
			throw std::runtime_error{std::format("failed to open {}", in_filename)};

		std::cout << "Enter a word to look for: ";
		std::string word;
		if (!(std::cin >> word))
			throw std::exception{"failed to read word string"};

		int line_num = 1;
		for (std::string line; std::getline(ist, line);) {
			if (contains_word(line, word))
				std::cout << std::format("{:04}\t{}", line_num, line);
			++line_num;
		}
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
