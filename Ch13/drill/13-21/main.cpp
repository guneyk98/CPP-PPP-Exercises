#include <string>
#include <iostream>
#include "PPP/std_lib_facilities.h"

struct Person {
	Person() {};
	Person(const std::string& f, const std::string& s, int aa);

	const std::string& first_name() const { return fn; }
	const std::string& second_name() const { return sn; }
	int age() const { return a; }
private:
	std::string fn;
	std::string sn;
	int a = 0;
};

std::ostream& operator<<(std::ostream& os, const Person& p);
std::istream& operator>>(std::istream& is, Person& p);

int main()
{
	try {
		Person p1{"Goofy", "Goof", 63};
		std::cout << p1.first_name() << ' ' << p1.second_name() << ' ' << p1.age() << '\n';

		/*Person p2;
		if (std::cin >> p2)
			std::cout << p2 << '\n';*/

		std::vector<Person> v;
		for (Person p; std::cin >> p; )
			v.push_back(p);

		for (const Person& p : v)
			std::cout << p << '\n';

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 1;
	}
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << p.first_name() << ' ' << p.second_name() << ' ' << p.age();
}

std::istream& operator>>(std::istream& is, Person& p)
{
	std::string fn;
	std::string sn;
	int age;
	if (is >> fn >> sn >> age)
		p = Person{fn, sn, age};
	return is;
}

Person::Person(const std::string& f, const std::string& s, int aa) : fn{f}, sn{s}
{
	if (aa < 0 || aa >= 150)
		error("age out of range");

	static const std::string invalid{";:\"'[]*&^%$#@!."};
	for (char inv_ch : invalid) {
		for (char ch : fn)
			if (ch == inv_ch)
				error("first name contains invalid chararcters");
		for (char ch : sn)
			if (ch == inv_ch)
				error("second name contains invalid chararcters");
	}
}
