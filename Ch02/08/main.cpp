import std;

int main()
{
	std::cout << "Enter an integer: ";
	int val = -1;
	std::cin >> val;
	std::cout << "The value " << val << " is an " <<
		(val%2 == 0 ? "even" : "odd") << " number.\n";
}
