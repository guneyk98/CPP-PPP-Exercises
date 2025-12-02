import std;

void print_array(std::ostream& os, int* a, int n)
{
	if (a == nullptr)
		return;
	for (int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << '\n';
}

void print_vec(std::ostream& os, std::vector<int>* v)
{
	if (v == nullptr)
		return;
	for (int x : *v)
		os << x << ' ';
	os << '\n';
}

int main()
{
	constexpr int Arr_size = 10;
	int* Arr = new int[Arr_size];
	for (int i = 0; i < Arr_size; ++i)
		std::cout << Arr[i] << ' ';
	std::cout << '\n';
	delete[] Arr;

	constexpr int Arr1_size = 10;
	int* Arr1 = new int[Arr1_size] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
	print_array(std::cout, Arr1, Arr1_size);
	delete[] Arr1;

	constexpr int Arr2_size = 11;
	int* Arr2 = new int[Arr2_size] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
	print_array(std::cout, Arr2, Arr2_size);
	delete[] Arr2;

	constexpr int Arr3_size = 20;
	int* Arr3 = new int[Arr3_size] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
		110, 111, 112, 113, 114, 115, 116, 117, 118, 119};
	print_array(std::cout, Arr3, Arr3_size);
	delete[] Arr3;

	std::vector<int>* Vec1 = new std::vector<int> {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
	print_vec(std::cout, Vec1);
	delete Vec1;

	std::vector<int>* Vec2 = new std::vector<int> {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
	print_vec(std::cout, Vec2);
	delete Vec2;

	std::vector<int>* Vec3 = new std::vector<int> {100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
		110, 111, 112, 113, 114, 115, 116, 117, 118, 119};
	print_vec(std::cout, Vec3);
	delete Vec3;

}