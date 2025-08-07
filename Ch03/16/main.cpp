import std;

int main()
{
	std::vector<std::string> strs;
	std::string input_str;

	for (;;) {
		std::cout << "Enter a string (| to quit): ";
		if (!(std::cin >> input_str)) {
			std::cout << input_str << "Failed to read valid string.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (input_str[0] == '|')
			break;

		strs.push_back(input_str);
	}

	if (strs.size() == 0) {
		std::cout << "\nNo strings entered.\n";
		return 0;
	}

	std::ranges::sort(strs);
	std::string mode = strs[0];
	int mode_count = 0;

	int count = 0;
	std::string str_to_count = strs[0];
	std::cout << "\nStrings: \n";
	for (std::string str : strs) {
		std::cout << str << "\n";

		if (str == str_to_count) {
			++count;
		} else {
			if (count > mode_count) {
				mode = str_to_count;
				mode_count = count;
			}
			count = 1;
			str_to_count = str;
		}
	}

	if (count > mode_count) {
		mode = str_to_count;
		mode_count = count;
	}

	std::cout << "Mode: " << mode << "\t" << "Count: " << mode_count << "\n";
	std::cout << "Max: " << strs.back() << "\t" << "Min: " << strs[0] << "\n";
	return 0;
}
