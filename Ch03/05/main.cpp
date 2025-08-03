import std;

int main()
{
	std::cout << "Think of a number between 1 and 100.\n";

	int min = 1, max = 100;
	std::string response;

	for (size_t i = 0; i < 7; ++i) {
		std::cout << "Is your number less than " <<  (min+max)/2 << "? (Y or N): \n";
		std::cin >> response;
		
		if (response == "Y") {
			max = (min+max)/2 - 1;
		} else if (response == "N") {
			min = (min+max)/2;
		} else {
			std::cout << "Incorrect input entered.\n";
			--i;
			continue;
		}

		if (min == max)
			break;
	}

	if (min == max)
		std::cout << "Your number is " <<  min << ".\n";
	else
		std::cout << "I don't know your number.\n";
}
