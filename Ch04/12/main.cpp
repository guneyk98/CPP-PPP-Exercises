import std;

bool contains_value(const std::vector<int>& v, int val)
{
	for (int n : v)
		if (n == val)
			return true;
	return false;
}

int main()
{
	try {
		std::vector<int> ans = {4,1,6,5};

		for (;;) {
			std::cout << "Enter your guess (eg 1234): ";
			std::vector<int> guess;

			int bulls = 0, cows = 0;
			char in_char = '\0';
			for (size_t i = 0; i < 4; ++i) {
				if (!(std::cin >> in_char) || in_char < '0' || in_char > '9')
					throw std::exception("Invalid input.");

				const int in_digit = in_char - '0';
				if (contains_value(guess, in_digit))
					throw std::exception("Duplicate digits entered.");
				guess.push_back(in_digit);

				for (size_t j = 0; j < 4; ++j) {
					if (in_digit == ans[j]) {
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
		return 1;
	}
}
