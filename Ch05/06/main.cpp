import std;

bool contains_char(const std::vector<char>& v, char val)
{
	for (char n : v)
		if (n == val)
			return true;
	return false;
}

int main()
{
	try {
		std::vector<char> ans = {'p','n','e','x'};

		for (;;) {
			std::cout << "Enter your guess (eg abcd): ";
			std::vector<char> guess;

			int bulls = 0, cows = 0;
			char in_char = '\0';
			for (size_t i = 0; i < 4; ++i) {
				if (!(std::cin >> in_char) || in_char < 'a' || in_char > 'z')
					throw std::exception("Invalid input.");

				if (contains_char(guess, in_char))
					throw std::exception("Duplicate digits entered.");
				guess.push_back(in_char);

				for (size_t j = 0; j < 4; ++j) {
					if (in_char == ans[j]) {
						i == j ? ++bulls : ++cows;
						break;
					}
				}
			}
			if (bulls == 4) {
				std::cout << "Your guess is correct!\n";
				break;
			}
			std::cout << bulls << (bulls == 1 ? " bull" : " bulls") <<
				" and " << cows << (cows == 1 ? " cow" : " cows") << ".\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
}