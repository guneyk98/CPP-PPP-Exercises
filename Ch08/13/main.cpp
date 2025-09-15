import std;
import Rational;

int main()
{
	try {
		Rational r1{-4, 12}, r2{7, 12};
		std::cout << r1 << " + " << r2 << " = " << r1+r2 << " (" << double(r1+r2) << ")\n";
		std::cout << r1 << " - " << r2 << " = " << r1-r2 << " (" << double(r1-r2) << ")\n";
		std::cout << r1 << " * " << r2 << " = " << r1*r2 << " (" << double(r1*r2) << ")\n";
		std::cout << r1 << " / " << r2 << " = " << r1/r2 << " (" << double(r1/r2) << ")\n";

		std::cout << "4/12 == 1/3: " << (Rational{4,12} == Rational{1,3} ? "true" : "false") << '\n';
		std::cout << "72/8 == 9: " << (Rational{72,8} == Rational{9,1} ? "true" : "false") << '\n';
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
