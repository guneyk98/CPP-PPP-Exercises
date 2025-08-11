import std;

int sum_values(const std::vector<int>& v)
{
	int sum = 0;
	for (int x : v)
		sum += x;
	return sum;
}

int main()
{
	try {
		std::vector<int> mon, tue, wed, thu, fri, sat, sun;
		int num_rejected = 0;

		std::cout << "Enter day of the week and value pairs (| to quit): ";
		for (;;) {
			std::string in_str;
			if (!(std::cin >> in_str))
				throw std::exception("Invalid input.");
			if (in_str[0] == '|')
				break;

			int in_value = 0;
			if (!(std::cin >> in_value))
				throw std::exception("Invalid input.");

			if (in_str == "Monday" || in_str == "monday" || in_str == "Mon" || in_str == "mon")
				mon.push_back(in_value);
			else if (in_str == "Tuesday" || in_str == "tuesday" || in_str == "Tue" || in_str == "tue")
				tue.push_back(in_value);
			else if (in_str == "Wednesday" || in_str == "wednesday" || in_str == "Wed" || in_str == "wed")
				wed.push_back(in_value);
			else if (in_str == "Thursday" || in_str == "thursday" || in_str == "Thu" || in_str == "thu")
				thu.push_back(in_value);
			else if (in_str == "Friday" || in_str == "friday" || in_str == "Fri" || in_str == "fri")
				fri.push_back(in_value);
			else if (in_str == "Saturday" || in_str == "saturday" || in_str == "Sat" || in_str == "sat")
				sat.push_back(in_value);
			else if (in_str == "Sunday" || in_str == "sunday" || in_str == "Sun" || in_str == "sun")
				sun.push_back(in_value);
			else
				++num_rejected;
		}

		std::cout << '\n';
		std::cout << "Mon: " << sum_values(mon) << '\n';
		std::cout << "Tue: " << sum_values(tue) << '\n';
		std::cout << "Wed: " << sum_values(wed) << '\n';
		std::cout << "Thu: " << sum_values(thu) << '\n';
		std::cout << "Fri: " << sum_values(fri) << '\n';
		std::cout << "Sat: " << sum_values(sat) << '\n';
		std::cout << "Sun: " << sum_values(sun) << '\n';
		std::cout << "\nNumber of rejected values: " << num_rejected << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 1;
	}
}
