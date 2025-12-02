import std;

int main()
{
	int n = 0;
	for (;;) {
		[[maybe_unused]] int* a = new int[512];
		++n;
		std::cout << sizeof(int[512])*n << " bytes allocated\n";
	}
}
