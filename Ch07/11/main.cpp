import std;

struct Values {
	double smallest, largest, median, mean;
};

Values compute_values(std::vector<double> v)
{
	if (v.size() == 0)
		throw std::runtime_error("empty vector in compute_values()");
	Values res;
	std::sort(v.begin(), v.end());
	res.smallest = v[0];
	res.largest = v[v.size()-1];
	res.median = v.size()%2 == 0 ? (v[v.size()/2]+v[v.size()/2 - 1])/2 : v[v.size()/2];
	res.mean = 0;
	for (double x : v)
		res.mean += x;
	res.mean /= v.size();
	return res;
}

int main()
{
	try {
		std::vector<double> v = {4.21, 2.12, 0.56, 12.10};
		Values values = compute_values(v);
		std::cout << "Smallest: " << values.smallest << '\n';
		std::cout << "Largest: " << values.largest << '\n';
		std::cout << "Median: " << values.median << '\n';
		std::cout << "Mean: " << values.mean << '\n';
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