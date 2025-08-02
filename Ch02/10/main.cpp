import std;

int main()
{
	std::cout << "Enter operation followed by two operands: ";
	std::string operation;
	double a = 0, b = 0;

	std::cin >> operation >> a >> b;

	double result = 0;
	if (operation == "+" || operation == "plus")
		result = a+b;
	else if (operation == "-" || operation == "minus")
		result = a-b;
	else if (operation == "*" || operation == "mul")
		result = a*b;
	else if (operation == "/" || operation == "div")
		result = a/b;
	else {
		std::cout << "bad operation entered\n";
		return -1;
	}

	std::cout << a << " " << operation << " " << b <<
		" = " << result << "\n";
	return 0;
}
