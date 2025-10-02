import std;
import roman;

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
	Expression
Expression:
	Term
	Expression "+" Term
	Expression "-" Term
Term:
	Primary
	Term "*" Primary
	Term "/" Primary
Primary:
	Number
	"(" Expression ")"
	"-" Primary
	"+" Primary
Number:
	Roman_int-literal
*/

class Token {
public:
	char kind;
	Roman_int value;
	Token() : kind{0} {}
	Token(char ch) : kind{ch} {}
	Token(char ch, Roman_int val) : kind{ch}, value{val} {}
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

void calculate();
Roman_int statement();
Roman_int expression();
Roman_int term();
Roman_int power();
Roman_int primary();

void clean_up_this_mess();

constexpr char number = '8';
constexpr char print = ';';
constexpr char quit = 'q';
constexpr char help = 'h';
constexpr char prompt[] = "> ";
constexpr char result[] = "= ";
constexpr char helpkey[] = "help";
constexpr char quitkey[] = "quit";

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
	case '+': case '-': case '*': case '/':
		return Token{ch};
	case '.':
	case 'I': case 'V': case 'X': case 'L': case 'C': case 'D': case 'M':
	{
		std::cin.putback(ch);
		Roman_int val;
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
			if (s == helpkey)
				return Token{help};
			if (s == quitkey)
				return Token{quit};
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

Roman_int statement()
{
	return expression();
}

Roman_int expression()
{
	Roman_int left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left = left + term();
			t = ts.get();
			break;
		case '-':
			left = left - term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

Roman_int term()
{
	Roman_int left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left = left * primary();
			t = ts.get();
			break;
		case '/':
		{
			left = left / primary();
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

Roman_int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		Roman_int d = expression();
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error{"')' expected"};
		return d;
	}
	case number:
		return t.value;
	case '-':
		return Roman_int{-primary().as_int()};
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
