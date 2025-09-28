import std;

bool isvowel(char ch)
{
	ch = std::tolower(ch);
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' ||ch == 'u';
}

int main()
{
	try {
		std::ifstream ist{"input.txt"};
		if (!ist)
			throw std::runtime_error{"failed to open input.txt"};

		std::ofstream ost{"output.txt"};
		if (!ost)
			throw std::runtime_error{"failed to open output.txt"};

		for (char ch; ist.get(ch);)
			if (!isvowel(ch))
				ost.put(ch);
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
