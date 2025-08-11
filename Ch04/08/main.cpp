import std;

int main()
{
	try {
		std::cout << "Please enter the number of values you want to sum: ";
		int N = 0;
		if (!(std::cin >> N))
			throw std::exception("Invalid input; not an integer.");
		if (N <= 0)
			throw std::exception("Number of values to sum is not positive.");
		std::cout << "Please enter some integers (press '|' to stop): ";

		int in_value;
		std::vector<int> values;
		for (;;) {
			if (!(std::cin >> in_value)) {
				char in_char = '\0';
				std::cin.clear();
				if (std::cin >> in_char && in_char == '|')
					break;
				throw std::exception("Invalid input; not an integer or '|'");
			}
			values.push_back(in_value);
		}

		if (N > values.size())
			throw std::exception("Number of values to sum is greater than the actual number of values.");

		int sum = 0;
		std::cout << "The sum of the first " << N << " numbers ( ";
		for (size_t i = 0; i < N; ++i) {
			sum += values[i];
			std::cout << values[i] << " ";
		}
		std::cout << ") is " << sum << ".\n";
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
