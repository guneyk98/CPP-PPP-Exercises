import std;

int main()
{
	std::vector<std::string> digit_strs = {"zero", "one", "two",
		"three", "four", "five", "six", "seven", "eight", "nine"};

	for (;;) {
		std::cout << "Enter a digit (0-9) as a word (lowercase) or numeral (q to quit): ";
		
		int input_int = -1;
		if (std::cin >> input_int) {
			if (input_int < 0 || input_int > 9) {
				std::cout << "Error: Digit out of range, try again.\n";
				continue;
			}
			std::cout << "Your digit is " << digit_strs[input_int] << ".\n";
		} else {
			std::cin.clear();
			std::string input_str;
			std::cin >> input_str;
			if (input_str == "q" || input_str == "Q")
				break;

			for (size_t i = 0; i < digit_strs.size(); ++i) {
				if (input_str == digit_strs[i]) {
					std::cout << "Your digit is " << i << ".\n";
					break;
				}
			}
		}
	}
}
