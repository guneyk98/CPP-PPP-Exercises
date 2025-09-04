import std;

double compute_index(const std::vector<double>& price, const std::vector<double>& weight)
{
	if (price.size() != weight.size())
		throw std::runtime_error("price and weight vectors have differing sizes");
	double res = 0;
	for (size_t i = 0; i < price.size(); ++i)
		res += price[i]*weight[i];
}

int main()
{
	try {
		std::vector<double> price = {4.21, 2.12, 0.56, 12.10};
		std::vector<double> weight = {1, 3.23, 1, 0.5};

		std::cout << compute_index(price, weight);
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