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

	std::cout << "\n";

	for (;;) {
		std::cout << "Enter score to search ('q' to quit): ";

		if (!(std::cin >> input_score)) {
			std::cin.clear();
			char input_char;
			if ((std::cin >> input_char) && (input_char == 'q' || input_char == 'Q'))
				break;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Failed to read valid score.\n";
			continue;
		}

		bool score_found = false;
		for (int i = 0; i < scores.size() && i < names.size(); ++i) {
			if (input_score == scores[i]) {
				std::cout << names[i] << " has a score of " << input_score << "\n";
				score_found = true;
				break;
			}
		}

		if (!score_found)
			std::cout << "Score not found.\n";
	}
}
