/*
Grammar for bitwise expressions:

Expression:
	Term_OR

Term_OR:
	Term_XOR
	Term_OR "|" Term_XOR

Term_XOR:
	Term_AND
	Term_XOR "^" Term_AND

Term_AND:
	Prefix
	Term_AND "&" Prefix

Prefix:
	"~" Prefix
	Primary

Primary:
	Number
	"(" Expression ")"

Number:
	unsigned-integer-literal
*/

import std;
#include <cassert>

class Token {
public:
	char kind;
	std::bitset<4> value;
	Token() {}
	Token(char k) : kind{k}, value{0b0000} {}
	Token(char k, std::bitset<4> v) : kind{k}, value{v} {}
};

class Token_stream {
public:
	Token get();
	void putback(Token t);
private:
	bool full = false;
	Token buffer;
} ts;

std::bitset<4> expression();
std::bitset<4> term_or();
std::bitset<4> term_xor();
std::bitset<4> term_and();
std::bitset<4> prefix();
std::bitset<4> primary();

int main()
{
	try {
		std::bitset<4> val{0};
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

	switch (ch) {
	case ';':
	case 'q':
	case '(': case ')':
	case '~': case '|': case '^': case '&':
		return Token{ch};
	case '0': case '1':
	{
		std::cin.putback(ch);
		std::bitset<4> val;
		std::cin >> val;
		return Token{'0', val};
	}
	default:
		throw std::exception{"Bad Token"};
	}
}

std::bitset<4> expression()
{
	return term_or();
}

std::bitset<4> term_or()
{
	std::bitset<4> left = term_xor();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '|':
			left |= term_xor();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

std::bitset<4> term_xor()
{
	std::bitset<4> left = term_and();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '^':
			left ^= term_and();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

std::bitset<4> term_and()
{
	std::bitset<4> left = prefix();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '&':
			left &= prefix();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

std::bitset<4> prefix()
{
	Token left = ts.get();
	std::bitset<4> val;
	switch (left.kind) {
	case '~':
		val = ~prefix();
		break;
	default:
		ts.putback(left);
		val = primary();
		break;
	}
	return val;
}

std::bitset<4> primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		std::bitset<4> d = expression();
		t = ts.get();
		if (t.kind != ')')
			throw std::exception{"')' expected"};
		return d;
	}
	case '0':
		return t.value;
	default:
		throw std::exception{"primary expected"};
	}
}
