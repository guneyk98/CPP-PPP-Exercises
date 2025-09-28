import std;

enum class Base { Dec, Oct, Hex };

struct Number {
	int n;
	Base base;
};

constexpr std::array base_format_tbl{std::dec, std::oct, std::hex};
constexpr std::array base_name_tbl{"decimal", "octal", "hexadecimal"};

std::istream& operator>>(std::istream& is, Number& n)
{
	int sign = 1;
	char ch;

	if (!(is >> ch))
		return is;

	if (ch == '-' || ch == '+') {
		sign = ch == '-' ? -1 : 1;
		if (!is.get(ch))
			return is;
	}

	if (!std::isdigit(ch)) {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}

	if (ch != '0') {
		n.base = Base::Dec;
		is.unget();
		is >> base_format_tbl[static_cast<int>(n.base)] >> n.n;
		n.n *= sign;
		return is;
	}

	if (!(is >> ch)) {
		if (is.eof()) {
			is.clear(std::ios::goodbit);
			n = Number{0, Base::Dec};
		}
		return is;
	}

	n.base = Base::Hex;
	if (ch != 'x' && ch != 'X') {
		n.base = Base::Oct;
		is.unget();
	}

	if (is >> base_format_tbl[static_cast<int>(n.base)] >> n.n)
		n.n *= sign;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const Number& n)
{
	return os << std::showbase << base_format_tbl[static_cast<int>(n.base)] << n.n;
}

std::string to_string(const Number& n)
{
	std::ostringstream is;
	is << n;
	return is.str();
}

int main()
{
	try {
		std::vector<Number> nums;
		for (;;) {
			std::cout << "Enter a number (q to finish): ";
			char ch;
			std::cin >> ch;
			if (ch == 'q')
				break;
			std::cin.unget();

			Number n;
			if (!(std::cin >> n)) {
				if (std::cin.bad())
					throw std::runtime_error{"std::cin is in bad state"};
				if (std::cin.eof())
					break;
				if (std::cin.fail()) {
					std::cerr << "Invalid input, try again.\n";
					std::cin.clear(std::ios::goodbit);
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
			}
			nums.push_back(n);
		}

		std::cout << '\n';
		for (const Number& x : nums) {

			std::cout <<
				std::format("{:^14}{:<16}{:<16}{:^14d}{:<16}\n",
							to_string(x),
							base_name_tbl[static_cast<int>(x.base)],
							"converts to",
							x.n,
							"decimal");

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
