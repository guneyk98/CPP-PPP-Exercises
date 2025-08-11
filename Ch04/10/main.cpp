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

		double in_value = 0;
		std::vector<double> values;
		std::cout << "Please enter some numbers (press '|' to stop): ";
		for (;;) {
			if (!(std::cin >> in_value)) {
				char in_char = '\0';
				std::cin.clear();
				if (std::cin >> in_char && in_char == '|')
					break;
				throw std::exception("Invalid input; not an valid number or '|'");
			}
			values.push_back(in_value);
		}

		if (N > values.size())
			throw std::exception("Number of values to sum is greater than the actual number of values.");

		double sum = values[0];
		std::vector<double> diffs;
		std::cout << "The sum of the first " << N << " numbers ( " << values[0] << " ";
		for (size_t i = 1; i < N; ++i) {
			sum += values[i];
			diffs.push_back(values[i] - values[i-1]);
			std::cout << values[i] << " ";
		}
		std::cout << ") is " << sum << ".\n";

		std::cout << "The differences between the first " << N << " numbers:\n";
		for (double diff : diffs)
			std::cout << diff << " ";
		std::cout << '\n';
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
