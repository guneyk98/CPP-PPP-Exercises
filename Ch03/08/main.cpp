import std;

std::vector<std::string> digit_strs = {"zero", "one", "two",
	"three", "four", "five", "six", "seven", "eight", "nine"};

int get_digit()
{
	int digit = -1;
	if (std::cin >> digit)
		return digit;

	std::cin.clear();
	std::string input_str;
	std::cin >> input_str;
	for (int i = 0; i < digit_strs.size(); ++i) {
		if (input_str == digit_strs[i])
			digit = i;
	}
	return digit;
}

int main()
{
	std::cout << "Enter two digits numeral or word (lowercase) followed by an operation: ";

	for (;;) {
		char op;
		int a = get_digit();
		int b = get_digit();
		if (a == -1 || b == -1) {
			std::cout << "Error: Invalid operands.\n";
			return -1;
		}
		std::cin >> op;

		switch (op) {
		case '+':
			std::cout << "The sum of " << a << " and " << b << " is " << a+b << ".\n";
			break;
		case '-':
			std::cout << "The difference of " << a << " and " << b << " is " << a-b << ".\n";
			break;
		case '*':
			std::cout << "The product of " << a << " and " << b << " is " << a*b << ".\n";
			break;
		case '/':
			std::cout << "The quotient of " << a << " and " << b << " is " << a/b << ".\n";
			break;
		default:
			std::cout << "Error: incorrect/unsupported operation entered.\n";
			break;
		}
	}
	return 0;
}
