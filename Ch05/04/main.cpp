import std;

class Name_value {
public:
	std::string name;
	int val = 0;
};

int main()
{
	std::vector<Name_value> nv_list;
	
	Name_value in_nv;
	for (;;) {
		std::cout << "Enter name and score ('NoName 0' to quit): ";
		std::cin >> in_nv.name >> in_nv.val;

		if (in_nv.name == "NoName")
			break;

		for (Name_value nv : nv_list) {
			if (nv.name == in_nv.name) {
				std::cout << "Error: duplicate name.\n";
				return 1;
			}
		}

		nv_list.push_back(in_nv);
	}

	std::cout << "\nNames and scores:\n";
	for (Name_value nv : nv_list)
		std::cout << nv.name << "\t" << nv.val << "\n";

	std::cout << "\n";

	for (;;) {
		std::cout << "Enter score to search ('q' to quit): ";

		int in_val = 0;
		if (!(std::cin >> in_val)) {
			std::cin.clear();
			char input_char = '\0';
			if ((std::cin >> input_char) && (input_char == 'q' || input_char == 'Q'))
				break;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Failed to read valid score.\n";
			continue;
		}

		bool score_found = false;
		for (int i = 0; i < nv_list.size(); ++i) {
			if (in_val == nv_list[i].val) {
				std::cout << nv_list[i].name << " has a score of " << nv_list[i].val << "\n";
				score_found = true;
				break;
			}
		}

		if (!score_found)
			std::cout << "Score not found.\n";
	}
}
