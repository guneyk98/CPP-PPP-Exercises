import std;


std::vector<int> primes;

bool is_prime(int num)
{
	for (int prime : primes)
		if (num % prime  == 0)
			return false;
	return true;
}

int main()
{
	int n = 0;
	std::cout << "Number of primes to find: ";
	std::cin >> n;

	for (int i = 2; ; ++i) {
		if (is_prime(i)) {
			primes.push_back(i);
			if (primes.size() >= n)
				break;
		}
	}

	std::cout << "Found primes: ";
	for (int prime : primes)
		std::cout << prime << " ";
	std::cout << "\n";
}
