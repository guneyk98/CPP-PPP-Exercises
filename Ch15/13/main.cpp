import std;

struct Link {
	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), prev{p}, succ{s} { }
	std::string value;
	Link* prev;
	Link* succ;
};

Link* insert(Link* p, Link* n); //insert before an element
Link* add(Link* p, Link* n); //insert after an element
Link* erase(Link* p); //remove an element
Link* find(Link* p, const std::string& s); //find a link with a given value
Link* advance(Link* p, int n); //get the nth successor
void delete_list(Link* p);
void print_all(Link* p);

int main()
{
	Link* norse_gods = new Link{"Thor"};
	norse_gods = insert(norse_gods, new Link{"Odin"});
	norse_gods = insert(norse_gods, new Link{"Zeus"});
	norse_gods = insert(norse_gods, new Link{"Freja"});

	Link* greek_gods = new Link{"Hera"};
	greek_gods = insert(greek_gods, new Link{"Athena"});
	greek_gods = insert(greek_gods, new Link{"Mars"});
	greek_gods = insert(greek_gods, new Link{"Poseidon"});

	Link* p = find(greek_gods, "Mars");
	if (p)
		p->value = "Ares";

	p = find(norse_gods, "Zeus");
	if (p) {
		if (p == norse_gods)
			norse_gods = p->succ;
		erase(p);
		greek_gods = insert(greek_gods, p);
	}

	print_all(norse_gods);
	std::cout << '\n';

	print_all(greek_gods);
	std::cout << '\n';

	delete_list(norse_gods);
	delete_list(greek_gods);
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
		if (p->value == s)
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

void delete_list(Link* p) {
	while (p) {
		Link* next = p->succ;
		delete p;
		p = next;
	}
}

void print_all(Link* p)
{
	std::cout << "{ ";
	while (p) {
		std::cout << p->value;
		if ((p = p->succ) != 0)
			std::cout << ", ";
	}
	std::cout << " }";
}
