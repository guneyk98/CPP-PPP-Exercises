import std;

int main()
{
	std::string s;

	for (;;) {
		char ch;
		std::cin >> ch;
		if (ch == '!')
			break;
		s += ch;
	}

	for (char ch : s)
		std::cout << ch;
}
