import std;

struct God {
	std::string name, mythology, vehicle, weapon;
};

bool operator==(const God& a, const God& b) { return a.name == b.name; }
bool operator!=(const God& a, const God& b) { return !(a == b); }
bool operator<(const God& a, const God& b) { return a.name < b.name; }
bool operator>(const God& a, const God& b) { return b < a; }
bool operator<=(const God& a, const God& b) { return !(a > b); }
bool operator>=(const God& a, const God& b) { return !(a < b); }

struct Link {
	Link(const God& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), prev{p}, succ{s} { }
	God value;
	Link* prev;
	Link* succ;

	Link* add_ordered(Link* p);
};

Link* insert(Link* p, Link* n); //insert before an element
Link* add(Link* p, Link* n); //insert after an element
Link* erase(Link* p); //remove an element
Link* find(Link* p, const God& g); //find a link with a given value
Link* advance(Link* p, int n); //get the nth successor
void print_all(Link* p);

int main()
{
	Link* gods = new Link{{"Thor", "Norse", "", "Mjolnir"}};
	gods = gods->add_ordered(new Link{{"Odin", "Norse", "Sleipner", "Gungnir"}});
	gods = gods->add_ordered(new Link{{"Zeus", "Greek", "", "lightning"}});
	print_all(gods);
}

Link* insert(Link* p, Link* n)
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return p;
	n->succ = p;
	if (p->prev)
		p->prev->succ = n;
	n->prev = p->prev;
	p->prev = n;
	return n;
}

Link* add(Link* p, Link* n)
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return p;
	n->prev = p;
	if (p->succ)
		p->succ->prev = n;
	n->succ = p->succ;
	p->succ = n;
	return n;
}

Link* erase(Link* p)
{
	if (p == nullptr)
		return nullptr;
	if (p->succ)
		p->succ->prev = p->prev;
	if (p->prev)
		p->prev->succ = p->succ;
	return p->succ;
}

Link* find(Link* p, const God& g)
{
	while (p) {
		if (p->value == g)
			return p;
		p = p->succ;
	}
	return nullptr;
}

Link* advance(Link* p, int n)
{
	if (p == nullptr)
		return nullptr;
	while (0 < n) {
		--n;
		if (p->succ)
			p = p->succ;
		return nullptr;
	}
	while (n < 0) {
		++n;
		if (p->prev)
			p = p->prev;
		return nullptr;
	}
	return p;
}

void print_all(Link* p)
{
	for (; p; p = p->succ) {
		std::cout << p->value.name << '\n';
		std::cout << "\tMythology: " << p->value.mythology << '\n';
		std::cout << "\tVehicle: " << p->value.vehicle << '\n';
		std::cout << "\tWeapon: " << p->value.weapon << '\n';
	}
}

Link* Link::add_ordered(Link* p)
{
	if (p == nullptr)
		return nullptr;

	if (p->value < value)
		return insert(this, p);

	Link* curr = this;
	while (curr->succ != nullptr && curr->succ->value < p->value)
		curr = curr->succ;

	add(curr, p);
	return this;
}
