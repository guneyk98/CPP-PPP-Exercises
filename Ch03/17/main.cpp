import std;

int main()
{	
	double a, b, c;

	std::cout << "Enter a: ";
	std::cin >> a;
	std::cout << "Enter b: ";
	std::cin >> b;
	std::cout << "Enter c: ";
	std::cin >> c;

	const double discrim = b*b - 4.0*a*c;
	if (discrim < 0) {
		std::cout << "Negative discriminant, complex numbers are not supported.\n";
		return 1;
	}

	const double x1 = (-b+std::sqrt(discrim))/(2.0*a);
	const double x2 = (-b-std::sqrt(discrim))/(2.0*a);

	std::cout << "x_1 = " << x1 << "\t" << "x_2 = " << x2;
}
