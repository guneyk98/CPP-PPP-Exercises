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

	std::cout << "\nNames and scores:\n";
	for (int i = 0; i < names.size() && i < scores.size(); ++i)
		std::cout << names[i] << "\t" << scores[i] << "\n";
}
