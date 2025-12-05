import std;

int str_cmp(const char* s1, const char* s2)
{
	if (s1 == nullptr || s2 == nullptr)
		return 0;

	while (*s1 && *s1 == *s2) {
		++s1;
		++s2;
	}
	return *s1 - *s2;
}

int main()
{
	std::cout << str_cmp("ac", "ab") << '\n';
}
