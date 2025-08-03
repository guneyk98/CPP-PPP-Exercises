import std;

constexpr int prime_max = 100;

int main()
{
	std::vector<bool> primes(prime_max+1, true);
	
	for (int p = 2; p < primes.size(); ++p) {
		if (primes[p] == false)
			continue;
		for (int i = 2*p; i < primes.size(); i += p)
			primes[i] = false;
	}

	std::cout << "Found primes: ";
	for (int i = 2; i < primes.size(); ++i)
		if (primes[i] == true)
			std::cout << i << " ";
	std::cout << "\n";
}
