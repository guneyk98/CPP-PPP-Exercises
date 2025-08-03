import std;

int main()
{
	std::cout << "Enter distances: ";
	std::vector<double> dists;
	for (double dist; std::cin >> dist; )
		dists.push_back(dist);

	double sum = 0;
	for (double x : dists)
		sum += x;

	std::cout << "Total distance: " << sum << "\n";
	std::cout << "Mean distance: " << sum/dists.size() << "\n";

	std::ranges::sort(dists);
	 
	std::cout << "Smallest distance: " << dists[0] << "\n";
	std::cout << "Greatest distance: " << dists.back() << "\n";

}
