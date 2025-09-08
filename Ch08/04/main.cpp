import std;

struct Name_pair {
	std::string name;
	double age;
};

class Name_pairs {
public:
	void read();
	void sort();
	const std::vector<Name_pair>& data() const { return np; }
private:
	void read_names();
	void read_ages();
	std::vector<Name_pair> np;
};

bool operator<(const Name_pair& lhs, const Name_pair& rhs);
bool operator==(const Name_pair& lhs, const Name_pair& rhs);
bool operator!=(const Name_pair& lhs, const Name_pair& rhs);
bool operator==(const Name_pairs& lhs, const Name_pairs& rhs);
bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs);
std::ostream& operator<<(std::ostream& os, const Name_pair& np);
std::ostream& operator<<(std::ostream& os, const Name_pairs& pairs);
bool name_exists(const std::string& s, const std::vector<Name_pair> pairs);

int main()
{
	try {
		Name_pairs np{};
		np.read();
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

void Name_pairs::read()
{
	read_names();
	read_ages();
}

void Name_pairs::sort()
{
	std::sort(np.begin(), np.end());
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
		if (name_exists(s, np))
			throw std::runtime_error("duplicate name");
		np.push_back({s, -1});
	}
}

void Name_pairs::read_ages()
{
	std::cout << "Enter the ages: ";
	for (int i = 0; i < np.size(); ++i) {
		double n;
		if (!(std::cin >> n))
			throw std::runtime_error("failed to read age");
		np[i].age = n;
	}
}

bool operator<(const Name_pair& lhs, const Name_pair& rhs)
{
	return lhs.name < rhs.name;
}

bool operator==(const Name_pair& lhs, const Name_pair& rhs)
{
	return lhs.name == rhs.name && lhs.age == rhs.age;
}

bool operator!=(const Name_pair& lhs, const Name_pair& rhs)
{
	return !(lhs == rhs);
}

bool operator==(const Name_pairs& lhs, const Name_pairs& rhs)
{
	return lhs.data() == rhs.data();
}

bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Name_pair& np)
{
	return std::cout << np.name << ", " << np.age;
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& nps)
{
	const std::vector<Name_pair>& pairs = nps.data();
	for (int i = 0; i < pairs.size(); ++i)
		std::cout << pairs[i] << '\n';
	return std::cout;
}

bool name_exists(const std::string& s, const std::vector<Name_pair> pairs)
{
	for (const Name_pair& x : pairs)
		if (s == x.name)
			return true;
	return false;
}
