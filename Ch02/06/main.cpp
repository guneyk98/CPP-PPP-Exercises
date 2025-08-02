import std;

int main()
{
	std::cout << "Enter three integers: ";
	double val1 = 0, val2 = 0, val3 = 0;
	std::cin >> val1 >> val2 >> val3;
	std::cout << "\n";

	if (val1 <= val2 && val1 <= val3) {
		if (val2 <= val3)
			std::cout << val1 << ", " << val2 << ", " << val3 << "\n";
		else
			std::cout << val1 << ", " << val3 << ", " << val2 << "\n";
	} else if (val2 <= val1 && val2 <= val3) {
		if (val1 <= val3)
			std::cout << val2 << ", " << val1 << ", " << val3 << "\n";
		else
			std::cout << val2 << ", " << val3 << ", " << val1 << "\n";
	} else {
		if (val1 <= val2)
			std::cout << val3 << ", " << val1 << ", " << val2 << "\n";
		else
			std::cout << val3 << ", " << val2 << ", " << val1 << "\n";
	}
}
