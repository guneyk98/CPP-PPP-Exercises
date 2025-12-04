import std;

struct Link {
	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), prev{p}, succ{s} { }
	std::string value;
	Link* prev;
	Link* succ;
};

Link* insert(Link* p, Link* n, Link* head); //insert before an element
Link* add(Link* p, Link* n); //insert after an element
Link* erase(Link* p, Link* head); //remove an element
Link* find(Link* p, const std::string& s); //find a link with a given value
Link* advance(Link* p, int n); //get the nth successor
void print_all(Link* p);

int main()
{
	Link* norse_gods = new Link{"Thor"};
	norse_gods = insert(norse_gods, new Link{"Odin"}, norse_gods);
	norse_gods = insert(norse_gods, new Link{"Zeus"}, norse_gods);
	norse_gods = insert(norse_gods, new Link{"Freja"}, norse_gods);

	Link* greek_gods = new Link{"Hera"};
	greek_gods = insert(greek_gods, new Link{"Athena"}, greek_gods);
	greek_gods = insert(greek_gods, new Link{"Mars"}, greek_gods);
	greek_gods = insert(greek_gods, new Link{"Poseidon"}, greek_gods);

	Link* p = find(greek_gods, "Mars");
	if (p)
		p->value = "Ares";

	p = find(norse_gods, "Zeus");
	if (p) {
		if (p == norse_gods)
			norse_gods = p->succ;
		erase(p, norse_gods);
		greek_gods = insert(greek_gods, p, greek_gods);
	}

	print_all(norse_gods);
	std::cout << '\n';

	print_all(greek_gods);
	std::cout << '\n';
}

Link* insert(Link* p, Link* n, Link* head)
{
	if (n == nullptr || p == nullptr)
		return head;

	if (p == head) {
		n->succ = head;
		return n;
	}
	Link* prev = head;
	while (prev && prev->succ != p)
		prev = prev->succ;

	if (prev) {
		prev->succ = n;
		n->succ = p;
	}
	return head;
}

Link* add(Link* p, Link* n)
{
	if (n == nullptr || p == nullptr)
		return p;
	n->succ = p->succ;
	p->succ = n;
	return n;
}

Link* erase(Link* p, Link* head)
{
	if (p == nullptr)
		return head;

	if (p == head)
		return head->succ;

	Link* prev = head;
	while (prev && prev->succ != p)
		prev = prev->succ;

	if (prev)
		prev->succ = p->succ;
	return head;
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
	return p;
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
