import std;

int main()
{
	std::vector<double> temps;
	for (double temp; std::cin >> temp; )
		temps.push_back(temp);

	double sum = 0;
	for (double x : temps)
		sum += x;
	std::cout << "Average temperature: " << sum/temps.size() << "\n";

	std::ranges::sort(temps);

	const size_t mid = temps.size()/2;
	std::cout << "Median temperature: " <<
		(temps.size()%2 == 0 ? (temps[mid] + temps[mid+1])/2 : temps[mid]) <<
		"\n";

}
