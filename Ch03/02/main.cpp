import std;

int main()
{
	std::cout << "Enter string: ";
	std::string s;
	std::cin >> s;

	for (char ch : s) {
		std::cout << ch << " has an int value of " << int{ch} << ".\n";
	}
}
