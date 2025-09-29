import std;


std::vector<std::string> split(const std::string& s, const std::string& w);
bool is_space(char ch);
bool in_string(const std::string& w, char ch);

int main()
{
	try {
		std::string w{";/"};
		for (std::string str; std::getline(std::cin, str);) {
			std::vector<std::string> v = split(str, w);
			for (const std::string& sub : v) {
				std::cout << sub << '\n';
			}
		}
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

std::vector<std::string> split(const std::string& s, const std::string& w)
{
	std::vector<std::string> res;
	std::string token;

	for (char ch : s) {
		if (is_space(ch) || in_string(w, ch)) {
			if (!token.empty()) {
				res.push_back(token);
				token.clear();
			}
			continue;
		}
		token.push_back(ch);
	}
	if (!token.empty())
		res.push_back(token);
	return res;
}

bool is_space(char ch)
{
	return std::isspace(static_cast<unsigned char>(ch));
}

bool in_string(const std::string& w, char ch)
{
	for (char x : w)
		if (ch == x)
			return true;
	return false;
}
