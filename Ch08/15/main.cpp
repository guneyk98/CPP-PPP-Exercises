import std;
import Money;

int main()
{
	try {
		std::cout << Money{Currency::USD, 43.20} << '\n';

		Money m1{Currency::USD, 12.36}, m2{Currency::GBP, 2.35};
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
