import std;

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

int main()
{
	try {
		std::vector<int> v{4, 2, 41, 123, 24123, 1, 0};
		Exercise::print(std::string{"Vector of integers:"}, v);
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