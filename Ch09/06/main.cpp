import std;

bool is_punct(char ch);
std::string& modify_str(std::string& str);

int main()
{
	try {
		for (std::string str; std::getline(std::cin, str);)
			std::cout << modify_str(str) << '\n';
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

bool is_punct(char ch)
{
	return ch == '.' || ch == ';' ||ch == ',' ||ch == '?' ||ch == '-' ||ch == '\'';
}

std::string& modify_str(std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '"') {
			//look for end of quote
			for (size_t j = i+1; j < str.size(); ++j) {
				if (str[j] == '"')
					i = j; //skip if found
			}
		}
		if (is_punct(str[i]))
			str[i] = ' ';
	}
	return str;
}
