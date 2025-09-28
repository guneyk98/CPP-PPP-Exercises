import std;

constexpr std::array<int (*)(int), 11> classification_func{
	std::isspace,
	std::isalpha,
	std::isdigit,
	std::isxdigit,
	std::isupper,
	std::islower,
	std::isalnum,
	std::iscntrl,
	std::ispunct,
	std::isprint,
	std::isgraph
};

constexpr std::array<const char*, 11> classification_str{
	"isspace",
	"isalpha",
	"isdigit",
	"isxdigit",
	"isupper",
	"islower",
	"isalnum",
	"iscntrl",
	"ispunct",
	"isprint",
	"isgraph"
};

std::ostream& print_classification(std::ostream& os, const std::string& str)
{
	for (const char& ch : str) {
		std::cout << ch << ": ";
		for (size_t i = 0; i < classification_func.size(); ++i)
			if (classification_func[i](ch))
				std::cout << classification_str[i] << ' ';
		std::cout << '\n';
	}
	return os;
}
int main()
{
	try {
		for (std::string str; std::cin >> str;)
			print_classification(std::cout, str);
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
