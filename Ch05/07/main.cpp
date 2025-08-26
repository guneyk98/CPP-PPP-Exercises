import std;

int digits_to_num(std::vector<char>& digits)
{
	int num = 0;
	for (char ch : digits)
		num = 10*num + (ch-'0');
	return num;
}

int main()
{
	try {
		std::vector<char> digits;

		std::cout << "Enter number (max 4 digits): ";

		char in_char = '\0';
		while (std::cin >> in_char) {
			if (std::cin.peek() == '\n')
				std::cin.clear(std::ios::eofbit);
			if (in_char < '0' || in_char > '9')
				throw std::exception{"Invalid input."};
			if (digits.size() >= 4)
				throw std::exception{"Number can't be more than 4 digits."};
			digits.push_back(in_char);
		}
		
		std::cout << digits_to_num(digits) << " is ";

		switch (digits.size()) {
		case 4:
			std::cout << digits[digits.size()-4] <<
				(digits[digits.size()-4] == '1' ? " thousand" : " thousands") <<
				" and ";
			[[fallthrough]];
		case 3:
			std::cout << digits[digits.size()-3] <<
				(digits[digits.size()-3] == '1' ? " hundred" : " hundreds") <<
				" and ";
			[[fallthrough]];
		case 2:
			std::cout << digits[digits.size()-2] <<
				(digits[digits.size()-2] == '1' ? " ten" : " tens") <<
				" and ";
			[[fallthrough]];
		case 1:
			std::cout << digits[digits.size()-1] <<
				(digits[digits.size()-1] == '1' ? " one." : " ones.");
			break;
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
