import std;
import Chrono;
using namespace Chrono;

int main()
{
	try {
		Chrono::Date d1{Year{2025}, Month::sep, 9};
		Chrono::Date d2{Year{2025}, Month::sep, 12};
		Chrono::Date d3{Year{2025}, Month::sep, 13};
		
		std::cout << "day of week " << d1 << ": " << day_of_week(d1) << '\n';
		std::cout << "day of week " << d2 << ": " << day_of_week(d2) << '\n';
		std::cout << "day of week " << d3 << ": " << day_of_week(d3) << '\n';
		std::cout << '\n';

		std::cout << "next work day " << d1 << ": " << next_workday(d1) << '\n';
		std::cout << "next work day " << d2 << ": " << next_workday(d2) << '\n';
		std::cout << "next work day " << d3 << ": " << next_workday(d3) << '\n';
		std::cout << '\n';

		for (int i = 1; i <= 31; ++i) {
			Chrono::Date d{Year{2025}, Month::jan, i};
			std::cout << "week of year " << d << ": " << week_of_year(d) << '\n';
		}

	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "exception \n";
		return 2;
	}
}
