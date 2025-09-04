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

std::vector<int> reverse1(const std::vector<int>& v)
{
	std::vector<int> v2;
	for (int i = v.size()-1; i >= 0; --i)
		v2.push_back(v[i]);
	return v2;
}

void reverse2(std::vector<int>& v)
{
	for (int i = 0; i < v.size()/2; ++i)
		std::swap(v[i], v[v.size()-1-i]);
}

int main()
{
	try {
		std::vector<int> v1{1,3,5,7,9};
		std::vector<int> v2 = reverse1(v1);
		std::vector<int> v3 = v1;
		reverse2(v3);


		Exercise::print(std::string{"v1:"}, v1);
		Exercise::print(std::string{"v2:"}, v2);
		Exercise::print(std::string{"v3:"}, v3);
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