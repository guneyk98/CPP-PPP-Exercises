import std;
import Chrono;
using namespace Chrono;

int main()
{
	try {
		//std::cout << "2020: " << (leapyear(Year{2020}) ? "leapyear" : "not leapyear") << '\n';
		//std::cout << "2000: " << (leapyear(Year{2000}) ? "leapyear" : "not leapyear") << '\n';
		//std::cout << "1900: " << (leapyear(Year{1900}) ? "leapyear" : "not leapyear") << '\n';
		//std::cout << "1800: " << (leapyear(Year{1800}) ? "leapyear" : "not leapyear") << '\n';
		//std::cout << "1700: " << (leapyear(Year{1700}) ? "leapyear" : "not leapyear") << '\n';
		//std::cout << "1600: " << (leapyear(Year{1600}) ? "leapyear" : "not leapyear") << '\n';

		Chrono::Date today{Year{2020}, Month::feb, 2};
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

		Chrono::Date d3 = today;
		d3.add_month(1);
		std::cout << "1 month after " << today << " : " << d3 << '\n';
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
