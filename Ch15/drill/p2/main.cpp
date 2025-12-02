import std;

void print_array(std::ostream& os, int* a, int n)
{
	if (a == nullptr)
		return;
	for (int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << '\n';
}

int main()
{
	int* p1 = new int{7};
	std::cout << p1 << '\t' << *p1 << '\n';

	int* p2 = new int[7] {1, 2, 4, 8, 16, 32, 64};
	std::cout << p2 << '\t';
	print_array(std::cout, p2, 7);

	int* p3 = p2;

	p2 = p1;
	p2 = p3;

	std::cout << p1 << '\t' << *p1 << '\n';
	std::cout << p2 << '\t';
	print_array(std::cout, p2, 6);

	delete p1;
	delete[] p2;

	p1 = new int[10] {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
	p2 = new int[10];

	for (int i = 0; i < 10; ++i)
		p2[i] = p1[i];

	std::cout << p1 << '\t';
	print_array(std::cout, p1, 10);
	std::cout << p2 << '\t';
	print_array(std::cout, p2, 10);
}