import std;

static constexpr double m_per_cm = 0.01;
static constexpr double m_per_in = 0.0254;
static constexpr double m_per_ft = 0.3048;

int main()
{
	double smallest = std::numeric_limits<double>::max();
	double largest = std::numeric_limits<double>::min();
	double n = 0;
	std::string unit;
	std::vector<double> values;

	for (;;) {
		std::cout << "Enter a number (| to quit): ";
		if (!(std::cin >> n)) {
			std::cin.clear();
			char input;
			if ((std::cin >> input) && input == '|')
				break;
			else {
				std::cout << n << "Failed to read valid number.\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

		if (!(std::cin >> unit)) {
			std::cout << n << "Failed to read valid unit.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		
		if (unit != "m") { //treat m as the base unit
			if (unit == "cm")
				n *= m_per_cm;
			else if (unit == "in")
				n *= m_per_in;
			else if (unit == "ft")
				n *= m_per_ft;
			else {
				std::cout << n << "Failed to read valid unit.\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}
		values.push_back(n);

		if (n < smallest) {
			smallest = n;
			std::cout << n << "m is the smallest number so far.\n";
		}
		if (n > largest) {
			largest = n;
			std::cout << n << "m is the largest number so far.\n";
		}
	}
	
	if (values.size() == 0) {
		std::cout << "\nNo values entered.\n";
		return 0;
	}

	std::ranges::sort(values);
	std::cout << "\nValues: \n";
	for (double val : values) {
		std::cout << val << "m\n";
	}
	return 0;
}
