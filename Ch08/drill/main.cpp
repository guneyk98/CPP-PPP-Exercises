import std;
import Chrono;

int main()
{
	try {
		Chrono::Date today{Chrono::Year{2020}, Chrono::Month::feb, 2};
		std::cout << "Today: " << today << '\n';
		
		Chrono::Date tomorrow = today;
		tomorrow.add_day(1);
		std::cout << "Tomorrow: " << tomorrow << '\n';

		Chrono::Date d1 = today;
		d1.add_day(27);
		std::cout << "27 days after " << today << " : " << d1 << '\n';

		Chrono::Date d2 = today;
		d2.add_day(365);
		std::cout << "365 days after " << today << " : " << d2 << '\n';
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
