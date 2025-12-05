import std;

char* str_dup(const char* s)
{
	if (s == nullptr)
		return nullptr;

	int len = 0;
	for (const char* p = s; *p; ++p)
		++len;
	
	char* ret = new char[len+1];
	for (int i = 0; i < len; ++i)
		ret[i] = s[i];
	ret[len] = '\0';

	return ret;
}

int main()
{
	char* str = str_dup("Hello World!");
	std::cout << str << '\n';
	delete[] str;
}
