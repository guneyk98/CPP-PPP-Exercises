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
Link* find(Link* p, const std::string& s); //find a link with a given value
Link* advance(Link* p, int n); //get the nth successor
Link* move(Link* p, Link* new_list, Link** old_list); //move element to a new list, returns the new list

void print_all(Link* p);

int main()
{
	Link* gods = new Link{{"Thor", "Norse", "", "Mjolnir"}};
	gods = gods->add_ordered(new Link{{"Odin", "Norse", "Sleipner", "Gungnir"}});
	gods = gods->add_ordered(new Link{{"Lugh", "Irish", "Enbarr", "Gae Assail"}});
	gods = gods->add_ordered(new Link{{"Zeus", "Greek", "", "Thunderbolt"}});
	gods = gods->add_ordered(new Link{{"Poseidon", "Greek", "Pegasus", "Trident"}});
	gods = gods->add_ordered(new Link{{"The Dagda", "Irish", "", "Lorg Mor"}});
	gods = gods->add_ordered(new Link{{"Freyr", "Norse", "Blodughofi", "Freyr's Sword"}});
	gods = gods->add_ordered(new Link{{"Ares", "Greek", "Aithon, Phlogios, Konabos and Phobos", "Spear"}});
	gods = gods->add_ordered(new Link{{"The Morrigan", "Irish", "", ""}});

	std::cout << "########################## Gods ##########################\n";
	print_all(gods);

	Link* greek_gods = move(find(gods, "Ares"), nullptr, &gods);
	greek_gods = move(find(gods, "Zeus"), greek_gods, &gods);
	greek_gods = move(find(gods, "Poseidon"), greek_gods, &gods);

	Link* norse_gods = move(find(gods, "Odin"), nullptr, &gods);
	norse_gods = move(find(gods, "Thor"), norse_gods, &gods);
	norse_gods = move(find(gods, "Freyr"), norse_gods, &gods);

	Link* irish_gods = move(find(gods, "The Morrigan"), nullptr, &gods);
	irish_gods = move(find(gods, "The Dagda"), irish_gods, &gods);
	irish_gods = move(find(gods, "Lugh"), irish_gods, &gods);

	std::cout << "\n####################### Greek Gods #######################\n";
	print_all(greek_gods);

	std::cout << "\n####################### Norse Gods #######################\n";
	print_all(norse_gods);

	std::cout << "\n####################### Irish Gods #######################\n";
	print_all(irish_gods);
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

Link* find(Link* p, const std::string& s)
{
	while (p) {
		if (p->value.name == s)
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

Link* move(Link* p, Link* new_list, Link** old_list)
{
	if (p == nullptr) //if find fails
		return new_list;
	erase(p);
	if (p == *old_list) //if moving the first element of the old list
		*old_list = (*old_list)->succ;
	p->prev = nullptr;
	p->succ = nullptr;
	if (new_list == nullptr)
		return p;
	return new_list->add_ordered(p);
}
