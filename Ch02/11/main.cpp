import std;

int main()
{
	std::cout << "How many pennies do you have? \n>";
	int pennies = 0;
	std::cin >> pennies;

	std::cout << "How many nickels do you have? \n>";
	int nickels = 0;
	std::cin >> nickels;

	std::cout << "How many dimes do you have? \n>";
	int dimes = 0;
	std::cin >> dimes;

	std::cout << "How many quarters do you have? \n>";
	int quarters = 0;
	std::cin >> quarters;

	std::cout << "How many half-dollar coins do you have? \n>";
	int half_dollar = 0;
	std::cin >> half_dollar;

	std::cout << "How many one-dollar coins do you have? \n>";
	int one_dollar = 0;
	std::cin >> one_dollar;

	if (pennies > 0)
		std::cout << "You have " << pennies << (pennies > 1 ? " pennies" : " penny") << ".\n";
	if (nickels > 0)
		std::cout << "You have " << nickels << (nickels > 1 ? " nickels" : " nickel") << ".\n";
	if (dimes > 0)
		std::cout << "You have " << dimes << (dimes > 1 ? " dimes" : " dime") << ".\n";
	if (quarters > 0)
		std::cout << "You have " << quarters << (quarters > 1 ? " quarters" : " quarter") << ".\n";
	if (half_dollar > 0)
		std::cout << "You have " << half_dollar << (half_dollar > 1 ? " half-dollar coins" : " half-dollar coin") << ".\n";
	if (one_dollar > 0)
		std::cout << "You have " << one_dollar << (one_dollar > 1 ? " one-dollar coins" : " one-dollar coin") << ".\n";

	const double total = 0.01*pennies + 0.05*nickels + 0.1*dimes + 0.25*quarters + 0.50*half_dollar + one_dollar;
	std::cout << "The value of all of your coins is $" << total << ".\n";
}
