import std;

int main()
{
	std::cout << "Enter an integer as text: ";
	std::string s;
	std::cin >> s;
	
	int i = -1;
	if (s == "zero")
		i = 0;
	else if (s == "one")
		i = 1;
	else if (s == "two")
		i = 2;
	else if (s == "three")
		i = 3;
	else if (s == "four")
		i = 4;

	if (i == -1)
		std::cout << s << " is not a number that I know.\n";
	else
		std::cout << s << " is the number " << i << ".\n";
}
