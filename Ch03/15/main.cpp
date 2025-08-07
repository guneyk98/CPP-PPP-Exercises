import std;

int main()
{
	std::vector<int> values;

	for (;;) {
		std::cout << "Enter a positive integer (| to quit): ";

		int n = -1;
		if (!(std::cin >> n)) {
			std::cin.clear();
			char input;
			if ((std::cin >> input) && input == '|')
				break;

			std::cout << "Failed to read valid positive integer.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n <= 0) {
			std::cout << n << " is not a postive integer.\n";
			continue;
		}
		values.push_back(n);
	}
	
	if (values.size() == 0) {
		std::cout << "\nNo values entered.\n";
		return 0;
	}

	std::ranges::sort(values);
	int mode = values[0];
	int mode_count = 0;

	int count = 0;
	int val_to_count = values[0];
	std::cout << "\nValues: \n";
	for (double val : values) {
		std::cout << val << "m\n";

		if (val == val_to_count) {
			++count;
		} else {
			if (count > mode_count) {
				mode = val_to_count;
				mode_count = count;
			}
			count = 1;
			val_to_count = val;
		}
	}

	if (count > mode_count) {
		mode = val_to_count;
		mode_count = count;
	}

	std::cout << "Mode: " << mode << "\t" << "Count: " << mode_count << "\n";
	return 0;
}
