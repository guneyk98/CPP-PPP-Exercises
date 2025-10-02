import std;

constexpr size_t num_classif = 11;

constexpr std::array<int (*)(int), num_classif> classif_func{
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

constexpr std::array<const char*, num_classif> classif_str{
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

struct classif_count {
	std::array<int, num_classif> data{};
};

classif_count file_classif(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs)
		throw std::runtime_error{std::format("couldn't open file {}", filename)};

	classif_count res;
	for (char ch; ifs.get(ch);) {
		for (size_t i = 0; i < num_classif; ++i)
			if (classif_func[i](ch))
				++res.data[i];
	}
	return res;
}

int main()
{
	try {
		classif_count count = file_classif("input.txt");
		for (size_t i = 0; i < num_classif; ++i)
			std::cout << classif_str[i] << ":\t" << count.data[i] << '\n';
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
