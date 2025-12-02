import std;

int main()
{
	constexpr size_t arr_size = 64;
	char* arr = new char[arr_size];

	int i = 0;
	for (; i < arr_size; ++i) {
		char ch;
		std::cin >> ch;
		if (ch == '!')
			break;
		arr[i] = ch;
	}

	for (int j = 0; j < i; ++j)
		std::cout << arr[j];
}
