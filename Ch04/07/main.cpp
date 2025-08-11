import std;
#include <cassert>

int main()
{
	try {
		double a = 0.0, b = 0.0, c = 0.0;
		std::cout << "Enter a, b and c: ";
		std::cin >> a >> b >> c;
		const double discrim = b*b - 4.0*a*c;
		if (discrim < 0)
			throw std::exception("Discriminant is negative; no real roots.");

		const double x1 = (-b+std::sqrt(discrim))/(2.0*a);
		const double x2 = (-b-std::sqrt(discrim))/(2.0*a);
		std::cout << "x_1 = " << x1 << "\t" << "x_2 = " << x2;

		assert((a*x1*x1 + b*x1 + c) < std::numeric_limits<double>::epsilon());
		assert((a*x2*x2 + b*x2 + c) < std::numeric_limits<double>::epsilon());
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 1;
	}
}
