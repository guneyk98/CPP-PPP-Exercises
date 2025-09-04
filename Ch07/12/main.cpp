import std;

void print_until_s(const std::vector<std::string>& v, const std::string& quit)
{
	for (const std::string& s : v) {
		if (s == quit)
			return;
		std::cout << s << '\n';
	}
}

void print_until_ss(const std::vector<std::string>& v, const std::string& quit)
{
	bool first = false;
	for (const std::string& s : v) {
		if (s == quit) {
			if (first == true)
				return;
			first = true;
		}
		std::cout << s << '\n';
	}
}

int main()
{
	try {
		std::vector<std::string> v{"apple", "banana", "pear", "orange", "banana", "orange"};

		std::cout << "Test 1:\n";
		print_until_s(v, "apple");
		std::cout << "\nTest 2:\n";
		print_until_s(v, "banana");
		std::cout << "\nTest 3:\n";
		print_until_s(v, "kiwi");

		std::cout << "\nTest 4:\n";
		print_until_ss(v, "apple");
		std::cout << "\nTest 5:\n";
		print_until_ss(v, "banana");
		std::cout << "\nTest 6:\n";
		print_until_ss(v, "kiwi");
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