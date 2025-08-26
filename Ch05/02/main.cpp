import std;

class Token {
public:
	char kind;
	double value;
	Token() {}
	Token(char k) : kind{k}, value{0.0} {}
	Token(char k, double v) : kind{k}, value{v} {}
};

class Token_stream {
public:
	Token get();
	void putback(Token t);
private:
	bool full = false;
	Token buffer;
} ts;

double primary();
double term();
double expression();

int main()
{
	try {
		double val = 0.0;
		while (std::cin) {
			Token t = ts.get();
			if (t.kind == 'q')
				break;
			if (t.kind == ';')
				std::cout << '=' << val << '\n';
			else
				ts.putback(t);
			val = expression();
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

void Token_stream::putback(Token t)
{
	if (full)
		throw std::exception{"putback() into a full buffer"};
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full) {
		full = false;
		return buffer;
	}
	char ch = 0;
	if (!(std::cin >> ch))
		throw std::exception{"no input"};

	switch(ch) {
		case ';':
		case 'q':
		case '(': case ')': case '{': case '}':
		case '+': case '-': case '*': case '/':
			return Token{ch};
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			std::cin.putback(ch);
			double val = 0;
			std::cin >> val;
			return Token{'8', val};
		}
		default:
			throw std::exception{"Bad Token"};
	}
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '{':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}')
			throw std::exception{"'}' expected"};
		return d;
	}
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			throw std::exception{"')' expected"};
		return d;
	}
	case '8':
		return t.value;
	default:
		throw std::exception{"primary expected"};
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
				throw std::exception{"divide by zero"};
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
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