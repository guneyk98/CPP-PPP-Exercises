import std;
#include <cassert>

long long factorial(int n)
{
	assert(n >= 0);
	long long res = 1ull;
	while (n) {
		if (res > std::numeric_limits<long long>::max()/n)
			throw std::overflow_error("Integer overflow while calculating factorial.");
		res *= n--;
	}
	return res;
}

long long permutations(int n, int r)
{
	assert(n > 0 && r > 0 && n >= r);
	long long res = 1ll;
	for (int i = n-r+1; i <= n; ++i) {
		if (res > std::numeric_limits<long long>::max()/i)
			throw std::overflow_error("Integer overflow while calculating permutation.");
		res *= i;
	}
	return res;
}

long long combinations(int n, int r)
{
	assert(n > 0 && r > 0 && n >= r);
	if (r > n-r) //nCr = nC(n-r), choose the cheaper version to avoid overflow
		return permutations(n, n-r) / factorial(n-r);
	return permutations(n, r) / factorial(r);
}

int main()
{
	try {
		int n, r;
		std::cout << "Enter n and r: ";
		if (!(std::cin >> n) || !(std::cin >> r))
			throw std::exception("Invalid input while reading int.");

		std::cout << "Calculate permutations or combinations? (p or c): ";
		char in_choice;
		if (!(std::cin >> in_choice))
			throw std::exception("Invalid input while reading char.");

		switch (in_choice) {
		case 'p': case 'P':
			std::cout << permutations(n, r) << " permutations.";
			break;
		case 'c': case 'C':
			std::cout << combinations(n, r) << " combinations.";
			break;
		default:
			throw std::exception("Invalid input entered for choice of calculation.");
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
}
