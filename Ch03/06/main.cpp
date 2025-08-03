import std;

int main()
{
	std::cout << "Enter two operands followed by an operation: ";
	char op;
	double a = 0, b = 0;

	std::cin >> a >> b >> op;

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
