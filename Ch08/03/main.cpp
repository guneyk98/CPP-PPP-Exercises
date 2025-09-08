import std;

class Name_pairs {
public:
	void read_names();
	void read_ages();
	void sort();
	const std::vector<std::string>& name() const { return n; }
	const std::vector<double>& age() const { return a; }
private:
	std::vector<std::string> n;
	std::vector<double> a;
};

bool operator==(const Name_pairs& lhs, const Name_pairs& rhs);
bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs);
std::ostream& operator<<(std::ostream& os, const Name_pairs& np);
bool is_in_vector(const std::string& s, const std::vector<std::string> v);

int main()
{
	try {
		Name_pairs np{};
		np.read_names();
		np.read_ages();
		np.sort();
		std::cout << np;
		
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

void Name_pairs::read_names()
{
	std::cout << "Enter unique names, followed by '|': ";
	for (;;) {
		std::string s;
		if (!(std::cin >> s))
			throw std::runtime_error("failed to read name");
		if (s == "|")
			break;
		if (is_in_vector(s, n))
			throw std::runtime_error("duplicate name");
		n.push_back(s);
	}
}

void Name_pairs::read_ages()
{
	std::cout << "Enter the ages: ";
	for (int i = 0; i < n.size(); ++i) {
		double n;
		if (!(std::cin >> n))
			throw std::runtime_error("failed to read age");
		a.push_back(n);
	}
}

void Name_pairs::sort()
{
	if (n.size() != a.size())
		throw std::runtime_error("name and age vectors have differing sizes");

	const std::vector<std::string> name_old = n;
	const std::vector<double> age_old = a;

	std::sort(n.begin(), n.end());
	a.clear();
	for (int i = 0; i < n.size(); ++i) {
		for (int j = 0; j < name_old.size(); ++j) {
			if (n[i] == name_old[j]) {
				a.push_back(age_old[j]);
				break;
			}
		}
	}
}

bool operator==(const Name_pairs& lhs, const Name_pairs& rhs)
{
	return lhs.name() == rhs.name() && lhs.age() == rhs.age();
}

bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& np)
{
	const std::vector<std::string>& name = np.name();
	const std::vector<double>& age = np.age();
	for (int i = 0; i < name.size() && i < age.size(); ++i)
		std::cout << name[i] << ", " << age[i] << '\n';
	return std::cout;
}

bool is_in_vector(const std::string& s, const std::vector<std::string> v)
{
	for (const std::string& x : v)
		if (s == x)
			return true;
	return false;
}
