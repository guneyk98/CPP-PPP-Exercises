import std;

constexpr int roman_min = 1; //I
constexpr int roman_max = 3999; //MMMCMXCIX

constexpr std::array<const char*, 13> roman_char_tbl{
	"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
};

constexpr std::array<int, 13> roman_num_tbl{
	1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
};

class Roman_int {
public:
	Roman_int() : val{1} {}
	Roman_int(int i) : val{i} {}
	Roman_int(const std::string& s);
	int as_int() const { return val; }
	
private:
	int val;
};

std::istream& operator>>(std::istream& is, Roman_int& r);
std::ostream& operator<<(std::ostream& os, const Roman_int& r);
bool is_roman(char ch);
bool is_valid_roman(const std::string& s);
int roman_to_int(const std::string& s);
std::string int_to_roman(int n);
int roman_value(char ch);

int main()
{
	try {
		for (;;) {
			Roman_int r;
			std::cout << "Enter a number (roman or int): ";
			if (!(std::cin >> r)) {
				std::cerr << "Failed to read number, try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cout << "Roman " << r << " equals " <<  r.as_int() << '\n';
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

Roman_int::Roman_int(const std::string& s)
{
	if (!is_valid_roman(s))
		throw std::runtime_error{"invalid roman numeral"};
	val = roman_to_int(s);
}

std::istream& operator>>(std::istream& is, Roman_int& r)
{
	//skip whitespace
	if (!(is >> std::ws))
		return is;

	//check for int
	char ch = is.peek();
	if (std::isdigit(static_cast<unsigned char>(ch))) {
		int n;
		is >> n;
		if (n < roman_min || n > roman_max) {
			is.clear(std::ios::failbit);
			return is;
		}
		r = Roman_int{n};
		return is;
	}
	//check for string
	if (!is_roman(ch)) {
		is.clear(std::ios::failbit);
		return is;
	}
	std::string s;
	while (is && is_roman(is.peek()))
		s += is.get();
	r = Roman_int{s};
	return is;
}

std::ostream& operator<<(std::ostream& os, const Roman_int& r)
{
	return os << int_to_roman(r.as_int());
}

bool is_roman(char ch)
{
	return ch == 'I' || ch == 'V' || ch == 'X' || ch == 'L' ||
		ch == 'C' || ch == 'D' || ch == 'M';
}

bool is_valid_roman(const std::string& s)
{
	if (s.empty()) return false;

	for (char ch : s)
		if (!is_roman(ch))
			return false;

	int value = roman_to_int(s);
	if (value < roman_min || value > roman_max) 
		return false;
	return s ==  int_to_roman(value);
}

int roman_to_int(const std::string& s)
{
	int sum = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		int n1 = roman_value(s[i]);
		if (i+1 >= s.size()) {
			sum += n1;
			break;
		}
		int n2 = roman_value(s[i+1]);
		if (n1 >= n2)
			sum += n1;
		else {
			sum += n2-n1;
			++i;
		}
	}
	return sum;
}

std::string int_to_roman(int n)
{
	if (n < roman_min || n > roman_max)
		throw std::runtime_error{std::format(
			"Roman_int contains unrepresentable value {}", n)};

	std::string s;
	for (int i = 0; i < roman_char_tbl.size(); ++i) {
		for (int j = 0; j < n/roman_num_tbl[i]; ++j)
			s += roman_char_tbl[i];
		n %= roman_num_tbl[i];
	}
	return s;
}

int roman_value(char ch)
{
	switch (ch) {
	case 'I': return 1;
	case 'V': return 5;
	case 'X': return 10;
	case 'L': return 50;
	case 'C': return 100;
	case 'D': return 500;
	case 'M': return 1000;
	default: return 0;
	}
}
