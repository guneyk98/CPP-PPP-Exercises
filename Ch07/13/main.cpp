import std;

std::vector<int> num_char(const std::vector<std::string>& v)
{
	std::vector<int> res;
	for (const std::string& s : v)
		res.push_back(s.length());
	return res;
}

std::string longest_str(const std::vector<std::string>& v)
{
	std::string res = v[0];
	for (const std::string& s : v)
		if (s.length() > res.length())
			res = s;
	return res;
}

std::string shortest_str(const std::vector<std::string>& v)
{
	std::string res = v[0];
	for (const std::string& s : v)
		if (s.length() < res.length())
			res = s;
	return res;
}

std::string max_str(const std::vector<std::string>& v)
{
	std::string res = v[0];
	for (const std::string& s : v)
		if (s > res)
			res = s;
	return res;
}

std::string min_str(const std::vector<std::string>& v)
{
	std::string res = v[0];
	for (const std::string& s : v)
		if (s < res)
		res = s;
		return res;
}

int main()
{
	try {
		std::vector<std::string> v{"kiwi", "banana", "pear", "orange", "apple"};
		std::vector<int> n = num_char(v);

		std::cout << "Number of chars:";
		for (int x : n)
			std::cout << x << " ";
		std::cout << '\n';

		std::cout << "Longest string: " << longest_str(v) << '\n';
		std::cout << "Shortest string: " << shortest_str(v) << '\n';
		std::cout << "Lexicographically first string: " << min_str(v) << '\n';
		std::cout << "Lexicographically last string: " << max_str(v) << '\n';
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