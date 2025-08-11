import std;

double ctof(double c)
{
	if (c < -273.25)
		throw std::runtime_error(std::to_string(c)+"C is below absolute zero");
	const double f = 1.8*c + 32.0;
	return f;
}

double ftoc(double f)
{
	if (f < -459.67)
		throw std::runtime_error(std::to_string(f)+"F is below absolute zero");
	const double c = (f-32.0) * (5.0/9.0);
	return c;
}

int main()
{
	try {
		double in_value = 0.0, out_value = 0.0;
		char in_unit = '\0', out_unit = '\0';
		std::cin >> in_value >> in_unit;
		switch (in_unit) {
		case 'C':
			out_value = ctof(in_value); out_unit = 'F'; 
			break;
		case 'F':
			out_value = ftoc(in_value); out_unit = 'C'; 
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
