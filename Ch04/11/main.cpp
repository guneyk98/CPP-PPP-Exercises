import std;

int main()
{
	try {
		std::cout << "Enter N: ";
		size_t N = 0;
		if (!(std::cin >> N) || N <= 0)
			throw std::exception("Error: not a valid N.");

		std::cout << "N=1\t1\n" << (N > 1 ? "N=2\t1\n" : "");
		if (N <= 2)
			return 0;

		int prev = 1, curr = 1, next = 0;
		for (size_t i = 3; i <= N; ++i) {
			if ((next = curr + prev) <= curr)
				throw std::exception("Next value exceeded int limit.");
			
			std::cout << "N=" << i << "\t" << next << "\n";
			prev = curr;
			curr = next;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 1;
	}
}
