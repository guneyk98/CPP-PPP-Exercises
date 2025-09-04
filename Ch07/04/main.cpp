import std;
#include <cassert>

//print already exists in std
namespace Exercise {
void print(const std::string& s, const std::vector<int>& v)
{
	std::cout << s << '\n';
	for (int x : v)
		std::cout << x << ' ';
	std::cout << '\n';
}
}

void fibonacci(int x, int y, std::vector<int>& v, int n)
{
	assert(v.size() == 0);
	if (n <= 0)
		return;
	v.push_back(x);
	if (n == 1)
		return;
	v.push_back(y);

	for (int i = 2; i < n; ++i) {
		if (x > std::numeric_limits<int>::max()-y)
			throw std::overflow_error("Integer overflow in fibonacci()");
		x += y;
		v.push_back(x);
		std::swap(x, y);
	}
}

int main()
{
	std::vector<int> v;
	try {
		fibonacci(1, 2, v, 100);
		Exercise::print(std::string{"Fibbonaci:"}, v);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cout << "Last value reached: " << v.back();
		return 1;
	}
	catch (...) {
		std::cerr << "exception \n";
		return 2;
	}
}