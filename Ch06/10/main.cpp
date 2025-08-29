import std;

/*
Calculation:
	Statement
	Help
	Print
	Quit
	Calculation Print Statement
	Calculation Print Help
	Calculation Print Quit
Help:
	"help"
Print:
	";"
Quit:
	"quit"
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
	Power
	Term "*" Power
	Term "/" Power
	Term "%" Power
Power:
	Primary
	Primary "^" Power
Primary:
	Number
	Name
	Name "=" Expression
	"(" Expression ")"
	"-" Primary
	"+" Primary
Number:
	integer-literal
Name:
	[a-zA-Z][a-zA-Z_0-9]*
*/

class Token {
public:
	char kind;
	int value;
	std::string name;
	Token() : kind{0} {}
	Token(char ch) : kind{ch} {}
	Token(char ch, int val) : kind{ch}, value{val} {}
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
} ts;

class Variable {
public:
	std::string name;
	int value;
	bool is_const;
	Variable(std::string n, int val, bool is_const = false)
		: name{n}, value{val}, is_const{is_const} {
	};
};

class Symbol_table {
public:
	int get(std::string s);
	void set(std::string s, int d);
	bool is_declared(std::string var);
	int declare(std::string var, int val, bool is_const = false);
private:
	std::vector<Variable> var_table;
} st;

void calculate();
int statement();
int declaration(char kind);
int expression();
int term();
int power();
int primary();

void clean_up_this_mess();

int narrow_int(double d);
//functions that throw an exception on int overflow or underflow
int safe_add(int a, int b);
int safe_sub(int a, int b);
int safe_mul(int a, int b);
int safe_div(int a, int b);
int safe_mod(int a, int b);
int safe_pow(int base, int exp);
int safe_neg(int a);

constexpr char number = '8';
constexpr char print = ';';
constexpr char quit = 'q';
constexpr char help = 'h';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char con = 'C';
constexpr char prompt[] = "> ";
constexpr char result[] = "= ";
constexpr char helpkey[] = "help";
constexpr char quitkey[] = "quit";
constexpr char declkey[] = "let";
constexpr char constkey[] = "const";

int main()
{
	try {
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
	std::cin.get(ch);
	while (std::isspace(ch)) { //skip white-space
		if (ch == '\n')
			return Token{print};
		std::cin.get(ch);
	}

	switch (ch) {
	case print:
	case '=':
	case '(': case ')':
	case '+': case '-': case '*': case '/': case '%': case '^':
		return Token{ch};
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);
		double val = 0;
		std::cin >> val;
		return Token{number, narrow_int(val)};
	}
	default:
		if (std::isalpha(ch)) {
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (std::isalnum(ch) || ch == '_'))
				s += ch;
			std::cin.putback(ch);
			if (s == helpkey)
				return Token{help};
			if (s == quitkey)
				return Token{quit};
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
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit)
			return;
		if (t.kind == help) {
			std::cout << "INFO: This is a program that computes integer arithmetic expressions. Enter 'q' to quit.\n"
				<< "USAGE: Enter a valid expression and press enter. Multiple expressions can be entered in one line, if separated by ';'.\n"
				<< "EXAMPLE: '4+3; (4-3)/5;\n"
				<< "AVAILABLE OPERATORS: '+' (Addition), '-' (Subtration), '*' (Multiplication), '/' (Division), '%' (Modulo), '=' (Reassignment), '(' and ')' (Parentheses).\n"
				<< "VARIABLES: Variables can be declared using the 'let' and 'const' commands. Eg: 'let x = 5'"
				<< "Variables declared with 'let' (not 'const') can be reassigned to a new value, using the '=' (assignment) operator.\n";
			continue;
		}
		ts.putback(t);
		std::cout << result << statement() << '\n';
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		clean_up_this_mess();
	}
}

int statement()
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

int declaration(char kind)
{
	Token t = ts.get();
	if (t.kind != name)
		throw std::runtime_error("name expected in declaration");
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error(std::string{"= missing in declartion of "} + t.name);
	int d = expression();
	st.declare(t.name, d, kind == con);
	return d;
}

int expression()
{
	int left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left = safe_add(left, term());
			t = ts.get();
			break;
		case '-':
			left = safe_sub(left, term());
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int term()
{
	int left = power();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left = safe_mul(left, power());
			t = ts.get();
			break;
		case '/':
		{
			int d = power();
			left = safe_div(left, d);
			t = ts.get();
			break;
		}
		case '%':
		{
			int d = power();
			left = safe_mod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

int power()
{
	int left = primary();
	Token t = ts.get();
	if (t.kind == '^') {
		int right = power();
		return safe_pow(left, right);
	}
	ts.putback(t);
	return left;

}

int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		int d = expression();
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
			int d = expression();
			st.set(t.name, d);
			return d;
		}
		ts.putback(n);
		return st.get(t.name);
	}
	case '-':
		return safe_neg(primary());
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

int Symbol_table::get(std::string s)
{
	for (const Variable& v : var_table)
		if (v.name == s)
			return v.value;
	throw std::runtime_error{std::string{"trying to read undefined variable "} + s};
}

void Symbol_table::set(std::string s, int d)
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

bool Symbol_table::is_declared(std::string var)
{
	for (const Variable& v : var_table)
		if (v.name == var)
			return true;
	return false;
}

int Symbol_table::declare(std::string var, int val, bool is_const)
{
	if (is_declared(var))
		throw std::runtime_error{var + std::string{" declared twice"}};
	var_table.push_back(Variable{var, val, is_const});
	return val;
}

int narrow_int(double d)
{
	int i = int(d);
	if (double(i) != d)
		throw std::runtime_error("narrowing error");
	return i;
}

int safe_add(int a, int b)
{
	if (b > 0 && (a > std::numeric_limits<int>::max()-b))
		throw std::overflow_error("integer overflow in addition");
	if (b < 0 && (a < std::numeric_limits<int>::min()-b))
		throw std::underflow_error("integer underflow in addition");
	return a+b;
}

int safe_sub(int a, int b)
{
	if (b < 0 && (a > std::numeric_limits<int>::max()+b))
		throw std::overflow_error("integer overflow in subtraction");
	if (b > 0 && (a < std::numeric_limits<int>::min()+b))
		throw std::underflow_error("integer underflow in subtraction");
	return a-b;
}

int safe_mul(int a, int b)
{
	if (a > 0) {
		if (b > 0) {
			if (a > std::numeric_limits<int>::max()/b)
				throw std::overflow_error("integer overflow in multiplication");
		} else {
			if (b < std::numeric_limits<int>::min()/a)
				throw std::underflow_error("integer underflow in multiplication");
		}
	} else {
		if (b > 0) {
			if (a < std::numeric_limits<int>::min()/b)
				throw std::underflow_error("integer underflow in multiplication");
		} else {
			if (a != 0 && b < std::numeric_limits<int>::max()/a)
				throw std::overflow_error("integer overflow in multiplication");
		}
	}
	return a*b;
}

int safe_div(int a, int b)
{
	if (b == 0)
		throw std::runtime_error{"divide by zero"};
	if (a == std::numeric_limits<int>::min() && b == -1)
		throw std::overflow_error{"integer underflow in division"};
	return a/b;
}

int safe_mod(int a, int b)
{
	if (b == 0)
		throw std::runtime_error{"divide by zero"};
	if (a == std::numeric_limits<int>::min() && b == -1)
		throw std::overflow_error{"integer overflow in modulo"};
	return a%b;
}

int safe_pow(int base, int exp)
{
	if (exp < 0)
		throw std::runtime_error("negative exponent not supported for integers");
	int result = 1;
	while (exp > 0) {
		if (exp % 2 == 1)
			result = safe_mul(result, base);
		exp /= 2;
		if (exp > 0)
			base = safe_mul(base, base);
	}
	return result;
}

int safe_neg(int a) //because -INT_MIN = INT_MAX+1
{
	if (a == std::numeric_limits<int>::min())
		throw std::overflow_error{"integer overflow in negation"};
	return -a;
}