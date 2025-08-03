import std;

constexpr int prime_max = 100;
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
	for (int i = 2; i < prime_max; ++i)
		if (is_prime(i))
			primes.push_back(i);

	std::cout << "Found primes: ";
	for (int prime : primes)
		std::cout << prime << " ";
	std::cout << "\n";
}
