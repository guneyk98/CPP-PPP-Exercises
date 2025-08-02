import std;

int main()
{
	std::cout << "Enter two integers: ";
	int val1 = 0, val2 = 0;
	std::cin >> val1 >> val2;
	std::cout << "\n";

	if (val1 == val2) {
		std::cout << "val1 is equal to val2\n";
	} else {
		std::cout << val1 << " is " <<
			(val1 > val2 ? "greater" : "smaller") <<
			" than " << val2 << "\n";
	}
	std::cout << val1 << " + " << val2 << " = " << val1+val2 << "\n";
	std::cout << val1 << " - " << val2 << " = " << val1-val2 << "\n";
	std::cout << val1 << " * " << val2 << " = " << val1*val2 << "\n";
	std::cout << val1 << " / " << val2 << " = " << val1/val2 << "\n";

}
