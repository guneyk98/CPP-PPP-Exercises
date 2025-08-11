import std;

double ctok(double c)
{
	if (c < -273.25)
		throw std::runtime_error(std::to_string(c)+"C is below absolute zero");
	const double k = c + 273.25;
	return k;
}

int main()
{
	try {
		double c = 0.0;
		std::cin >> c;
		double k = ctok(c);
		std::cout << k << '\n';
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
