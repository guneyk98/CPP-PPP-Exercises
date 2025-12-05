import std;

const char* find_x(const char* s, const char* x)
{
	if (s == nullptr || x == nullptr)
		return nullptr;
	if (*x == '\0')
		return s;

	for (; *s; ++s) {
		const char* ps = s;
		const char* px = x;

		while (*ps && *px && *ps == *px) {
			++ps;
			++px;
		}
		if (*px == '\0')
			return s;
	}
	return nullptr;
}

int main()
{
	const char str[] = "xvxcvhehellokjljkgfn,mcvnb";
	const char word[] = "hello";
	const char* p = find_x(str, word);
	
	if (p == nullptr)
		return 1;

	std::cout.write(p, std::strlen(word));
	std::cout << '\n';
	std::cout << "Found at position " << p-str << '\n';
}
