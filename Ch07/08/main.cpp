import std;

void print_name_age(const std::vector<std::string>& name, const std::vector<double>& age)
{
	for (int i = 0; i < name.size() && i < age.size(); ++i)
		std::cout << name[i] << ", " << age[i] << '\n';
}

void sort_name_age(std::vector<std::string>& name, std::vector<double>& age)
{
	if (name.size() != age.size())
		throw std::runtime_error("name and age vectors have differing sizes");

	const std::vector<std::string> name_old = name;
	const std::vector<double> age_old = age;

	std::sort(name.begin(), name.end());
	age.clear();
	for (int i = 0; i < name.size(); ++i) {
		for (int j = 0; j < name_old.size(); ++j) {
			if (name[i] == name_old[j]) {
				age.push_back(age_old[j]);
				break;
			}
		}
	}
}

bool is_in_vector(const std::string& s, const std::vector<std::string> v)
{
	for (const std::string& x : v)
		if (s == x)
			return true;
	return false;
}

int main()
{
	try {
		std::vector<std::string> name;
		std::cout << "Enter unique names, followed by '|': ";
		for (;;) {
			std::string s;
			if (!(std::cin >> s))
				throw std::runtime_error("failed to read name");
			if (s == "|")
				break;
			if (is_in_vector(s, name))
				throw std::runtime_error("duplicate name");
			name.push_back(s);
		}

		std::vector<double> age;
		std::cout << "Enter the ages: ";
		for (int i = 0; i < name.size(); ++i) {
			double n;
			if (!(std::cin >> n))
				throw std::runtime_error("failed to read age");
			age.push_back(n);
		}

		std::cout << "Unsorted: \n";
		print_name_age(name, age);

		sort_name_age(name, age);
		std::cout << "\nSorted: \n";
		print_name_age(name, age);

	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "exception \n";
		return 2;
	}
}