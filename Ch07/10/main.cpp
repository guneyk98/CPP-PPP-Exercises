import std;

double maxv(const std::vector<double>& v)
{
	if (v.size() == 0)
		throw std::runtime_error("empty vector in maxv");
	double largest = v[0];
	for (double x : v)
		if (x > largest)
			largest = x;
	return largest;
}

int main()
{
	try {
		std::vector<double> v = {4.21, 2.12, 0.56, 12.10, 4.33};
		std::cout << maxv(v);
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