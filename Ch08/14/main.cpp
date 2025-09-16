import std;
import Money;

int main()
{
	try {
		std::cout << Money{43, 2} << '\n';

		Money m1{12, 36}, m2{2, 35};
		std::cout << m1 << " + " << m2 << " = " << m1+m2 << '\n';
		std::cout << m1 << " - " << m2 << " = " << m1-m2 << '\n';
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
