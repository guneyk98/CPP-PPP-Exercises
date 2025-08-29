import std;

/*
Calculation:
	Statement
	Print
	Quit
	Calculation Print Statement
Print:
	";"
Quit:
	"q"
Statement:
	Declaration
	Expression
Declaration:
	"const" Name "=" Expression
	"let" Name "=" Expression
Expression:
	Term
	Expression "+" Term
	Expression "-" Term
Term:
	Primary
	Term "*" Primary
	Term "/" Primary
	Term "%" Primary
Primary:
	Number
	Name
	Name "=" Expression
	"(" Expression ")"
	"-" Primary
	"+" Primary
Number:
	floating-point-literal
Name:
	[a-zA-Z][a-zA-Z_0-9]*
*/

class Token {
public:
	char kind;
	double value;
	std::string name;
	Token() : kind{0}  {}
	Token(char ch) : kind{ch} {}
	Token(char ch, double val) : kind{ch}, value{val} {}
	Token(char ch, std::string n) : kind{ch}, name{n} {}
};

class Token_stream {
public:
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full = false;
	Token buffer;
};

class Variable {
public:
	std::string name;
	double value;
	bool is_const;
	Variable(std::string n, double val, bool is_const = false)
		: name{n}, value{val}, is_const{is_const} {};
};

void calculate();
double statement();
double declaration(char kind);
double expression();
double term();
double primary();

void clean_up_this_mess();
double get_value(std::string s);
void set_value(std::string s, double d);
bool is_declared(std::string var);
double define_name(std::string var, double val, bool is_const = false);

constexpr char number = '8';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char con = 'C';
constexpr char prompt[] = "> ";
constexpr char result[] = "= ";
constexpr char declkey[] = "let";
constexpr char constkey[] = "const";

Token_stream ts;
std::vector<Variable> var_table;

int main()
{
	try {
		define_name("pi", 3.1415926535, true);
		define_name("e", 2.7182818284, true);
		
		calculate();
		return 0;
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

Token Token_stream::get()
{
	if (full) {
		full = false;
		return buffer;
	}
	char ch = 0;
	if (!(std::cin >> ch))
		throw std::runtime_error{"no input"};

	switch (ch) {
	case quit:
	case print:
	case '=':
	case '(': case ')':
	case '+': case '-': case '*': case '/': case '%':
		return Token{ch};
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);
		double val = 0;
		std::cin >> val;
		return Token{number, val};
	}
	default:
		if (std::isalpha(ch)) {
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (std::isalnum(ch) || ch == '_'))
				s += ch;
			std::cin.putback(ch);
			if (s == declkey)
				return Token{let};
			if (s == constkey)
				return Token{con};
			return Token{name, s};
		}
		throw std::runtime_error{"Bad Token"};
	}
}

void Token_stream::putback(Token t)
{
	if (full)
		throw std::runtime_error{"putback() into a full buffer"};
	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (std::cin.get(ch))
		if (ch == c || ch == '\n')
			return;
}

void calculate()
{
	while (std::cin)
	try {
		std::cout << prompt;
		Token t = ts.get();
		if (t.kind == print)
			t = ts.get();
		if (t.kind == quit)
			return;
		ts.putback(t);
		std::cout << result << statement() << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		clean_up_this_mess();
	}
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case con:
	case let:
		return declaration(t.kind);
	default:
		ts.putback(t);
		return expression();
	}
}

double declaration(char kind)
{
	Token t = ts.get();
	if (t.kind != name)
		throw std::runtime_error("name expected in declaration");
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error(std::string{"= missing in declartion of "} + t.name);
	double d = expression();
	define_name(t.name, d, kind == con);
	return d;
}

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0)
				throw std::runtime_error{"divide by zero"};
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0)
				throw std::runtime_error{"divide by zero"};
			left = std::fmod(left,d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error{"')' expected"};
		return d;
	}
	case number:
		return t.value;
	case name:
	{
		Token n = ts.get();
		if (n.kind == '=') {
			double d = expression();
			set_value(t.name, d);
			return d;
		}
		ts.putback(n);
		return get_value(t.name);
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	default:
		throw std::runtime_error{"primary expected"};
	}
}

void clean_up_this_mess()
{
	ts.ignore(print);
}

double get_value(std::string s)
{
	for (const Variable& v : var_table)
		if (v.name == s)
			return v.value;
	throw std::runtime_error{std::string{"trying to read undefined variable "} + s};
}

void set_value(std::string s, double d)
{
	for (Variable& v : var_table) {
		if (v.name == s) {
			if (v.is_const)
				throw std::runtime_error{std::string{s + " is a constant"}};
			v.value = d;
			return;
		}
	}
	throw std::runtime_error{std::string{"trying to write undefined variable "} + s};
}

bool is_declared(std::string var)
{
	for (const Variable& v : var_table)
		if (v.name == var)
			return true;
	return false;
}

double define_name(std::string var, double val, bool is_const)
{
	if (is_declared(var))
		throw std::runtime_error{var + std::string{" declared twice"}};
	var_table.push_back(Variable{var, val, is_const});
	return val;
}


