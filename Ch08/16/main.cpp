import std;
import Money;

int main()
{
	try {
		Money m1, m2;
		std::cout << "Enter first currency value: ";
		if (!(std::cin >> m1)) {
			std::cerr << "Failed to read value.\n";
			return 1;
		}
		std::cout << "Enter second currency value: ";
		if (!(std::cin >> m2)) {
			std::cerr << "Failed to read value.\n";
			return 1;
		}

		std::cout << m1 << " + " << m2 << " = " << m1+m2 << '\n';
		std::cout << m1 << " - " << m2 << " = " << m1-m2 << '\n';
		std::cout << m2 << " + " << m1 << " = " << m2+m1 << '\n';
		std::cout << m2 << " - " << m1 << " = " << m2-m1 << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "exception \n";
		return 2;
	}
}
