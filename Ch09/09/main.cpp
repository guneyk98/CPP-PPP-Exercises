import std;

std::vector<std::string> split(const std::string& s)
{
	std::vector<std::string> v;
	std::istringstream is{s};
	for (std::string sub; is >> sub;)
		v.push_back(sub);
	return v;
}

int main()
{
	try {
		for (std::string str; std::getline(std::cin, str);) {
			std::vector<std::string> v = split(str);
			for (const std::string& sub : v) {
				std::cout << sub << '\n';
			}
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
