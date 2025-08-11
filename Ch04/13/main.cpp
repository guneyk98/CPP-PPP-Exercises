import std;
#include <cassert>

constexpr size_t num_digits = 4;

bool contains_value(const std::vector<int>& v, int val)
{
	for (int n : v)
		if (n == val)
			return true;
	return false;
}

std::vector<int> rand_unique_digits(size_t n, std::default_random_engine& engine)
{
	assert(n <= 10);
	std::uniform_int_distribution<int> dist(0, 9);
	std::vector<int> v;

	for (size_t i = 0; i < n; ++i) {
		int n = -1;
		do {
			n = dist(engine);
		} while (contains_value(v, n));
		v.push_back(n);
	}
	return v;
}

int main()
{
	try {
		std::cout << "Enter seed: ";
		unsigned int seed = 0;
		if (!(std::cin >> seed))
			throw std::exception("Invalid seed.");
		std::default_random_engine engine;
		engine.seed(seed);

		std::vector<int> ans = rand_unique_digits(num_digits, engine);

		for (;;) {
			std::cout << "Enter your guess (eg 1234): ";
			std::vector<int> guess;

			int bulls = 0, cows = 0;
			char in_char = '\0';
			for (size_t i = 0; i < num_digits; ++i) {
				if (!(std::cin >> in_char) || in_char < '0' || in_char > '9')
					throw std::exception("Invalid input.");

				int in_digit = in_char - '0';
				if (contains_value(guess, in_digit))
					throw std::exception("Duplicate digits entered.");
				guess.push_back(in_digit);

				for (size_t j = 0; j < num_digits; ++j) {
					if (in_digit == ans[j]) {
						i == j ? ++bulls : ++cows;
						break;
					}
				}
			}
			if (bulls == num_digits) {
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
