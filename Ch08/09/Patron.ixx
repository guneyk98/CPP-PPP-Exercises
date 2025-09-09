export module Patron;

import std;

export class Patron {
public:
	Patron(std::string name, int card_num, double fees = 0.0);

	const std::string& name() const { return _name; }
	int card_num() const { return _card_num; }
	double fees() const { return _fees; }

	void set_fees(double n);
private:
	std::string _name;
	int _card_num;
	double _fees;
};

export bool patron_owes_fees(const Patron& p);

export std::ostream& operator<<(std::ostream& os, const Patron& p);
export bool operator==(const Patron& lhs, const Patron& rhs);
export bool operator!=(const Patron& lhs, const Patron& rhs);

//Implementation

Patron::Patron(std::string name, int card_num, double fees)
	: _name{name}, _card_num{card_num}, _fees{fees}
{
}

void Patron::set_fees(double n)
{
	if (n < 0.0)
		throw std::exception{"Can't set negative fees"};
	_fees = n;
}

bool patron_owes_fees(const Patron& p)
{
	return p.fees() > 0.0;
}

std::ostream& operator<<(std::ostream& os, const Patron& p)
{
	return os <<
		"Patron Name: " << p.name() << '\n' <<
		"Library Card Number: " << p.card_num() << '\n' <<
		"Fees: " << p.fees() << '\n';
}

bool operator==(const Patron& lhs, const Patron& rhs)
{
	//Assuming card_num is unique for each user
	return lhs.card_num() == rhs.card_num();
}

bool operator!=(const Patron& lhs, const Patron& rhs)
{
	return !(lhs==rhs);
}