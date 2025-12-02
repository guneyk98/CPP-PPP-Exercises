import std;

int static_var;

struct Region {
	std::uintptr_t addr;
	const char* name;
};

void check_stack_growth(int* p)
{
	int a;
	std::cout << "First stack variable: " << p << '\n';
	std::cout << "Second stack variable: " << &a << '\n';
	if (p < &a)
		std::cout << "Stack grows upwards\n\n";
	else
		std::cout << "Stack grows downwards\n\n";
}

int main()
{
	int stack_var;
	int* heap_var = new int;

	std::cout << "Static variable: " << &static_var << '\n';
	std::cout << "Stack variable: " << &stack_var << '\n';
	std::cout << "Heap variable: " << heap_var << '\n';

	std::array<Region, 3> regions {
		Region{reinterpret_cast<uintptr_t>(&static_var), "static"},
		Region{reinterpret_cast<uintptr_t>(&stack_var), "stack"},
		Region{reinterpret_cast<uintptr_t>(&heap_var), "heap"}
	};
	std::sort(regions.begin(), regions.end(), [](const Region& a, const Region& b) {
		return a.addr < b.addr;
	});

	std::cout << "Memory order: ";
	for (int i = 0; i < regions.size(); ++i)
		std::cout << regions[i].name << (i == regions.size()-1 ? "\n\n" : " < ");

	check_stack_growth(&stack_var);

	int* arr = new int[5];
	for (int i = 0; i < 5; ++i)
		std::cout << "&arr[" << i << "] = " << &arr[i] << "\n";

	if (&arr[1] > &arr[0])
		std::cout << "Higher array indices -> higher addresses\n";
	else
		std::cout << "Higher array indices -> lower addresses\n";
}
