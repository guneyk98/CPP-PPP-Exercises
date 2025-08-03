import std;

int squares_required(int min_rice)
{
	int rice = 1;
	for (int square = 1; square < 64; ++square) {
		std::cout << "Squares: " << square << "\tRice: " << rice << "\n";

		if (rice >= min_rice)
			return square;
		rice *= 2;
	}
}

int main()
{
	std::cout << squares_required(1'000) << " squares are needed for 1,000 rice.\n\n";
	std::cout << squares_required(1'000'000) << " squares are needed for 1,000,000 rice.\n\n";
	std::cout << squares_required(1'000'000'000) << " squares are needed for 1,000,000,000 rice.\n\n";

}
