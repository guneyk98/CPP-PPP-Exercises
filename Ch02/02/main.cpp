import std;

int main()
{
	constexpr double km_per_mile = 1.609;

	std::cout << "Miles: ";
	double miles = -1;
	std::cin >> miles;
	std::cout << miles*km_per_mile << "km\n";

}
