import std;

double ctok(double c)
{
	if (c < -273.25)
		throw std::runtime_error(std::to_string(c)+"C is below absolute zero");
	const double k = c + 273.25;
	return k;
}

double ktoc(double k)
{
	if (k < 0)
		throw std::runtime_error(std::to_string(k)+"K is below absolute zero");
	const double c = k - 273.25;
	return k;
}

int main()
{
	try {
		double in_value = 0.0, out_value = 0.0;
		char in_unit = '\0', out_unit = '\0';
		std::cin >> in_value >> in_unit;
		switch (in_unit) {
		case 'C':
			out_value = ctok(in_value); out_unit = 'K'; 
			break;
		case 'K':
			out_value = ktoc(in_value); out_unit = 'C'; 
			break;
		default:
			throw std::runtime_error(in_unit+std::string(" is not a valid unit"));
			break;
		}
		std::cout << out_value << out_unit << '\n';
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
