import std;

int main()
{
	std::vector<std::string> names;
	std::vector<int> scores;

	std::string input_name;
	int input_score = 0;
	for (;;) {
		std::cout << "Enter name and score ('NoName 0' to quit): ";
		std::cin >> input_name >> input_score;

		if (input_name == "NoName")
			break;

		for (std::string name : names) {
			if (input_name == name) {
				std::cout << "Error: duplicate name.\n";
				return 1;
			}
		}

		names.push_back(input_name);
		scores.push_back(input_score);
	}
	std::cout << "\n";

	for (;;) {
		std::cout << "Enter name to search ('q' to quit): ";
		std::cin >> input_name;

		if (input_name == "q" || input_name == "Q")
			break;

		bool name_found = false;
		for (int i = 0; i < names.size() && i < scores.size(); ++i) {
			if (input_name == names[i]) {
				std::cout << input_name << " has a score of " << scores[i] << "\n";
				name_found = true;
				break;
			}
		}

		if (!name_found)
			std::cout << "Name not found.\n";
	}
}
