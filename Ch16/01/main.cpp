import std;

void to_lower(char* s)
{
	if (s == nullptr)
		return;

	for (; *s; ++s)
		if (*s >= 'A' && *s <= 'Z')
			*s -= 'A'-'a';
}

int main()
{
	char str[] = "Hello World!";
	to_lower(str);
	std::cout << str << '\n';
}
