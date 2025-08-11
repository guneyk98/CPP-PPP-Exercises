import std;

double ctok(double c)
{
	const double k = c + 273.25;
	return k;
}

int main()
{
	double c = 0.0;
	std::cin >> c;
	double k = ctok(c);
	std::cout << k << '\n';
}
