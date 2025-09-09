import std;
import Chrono;
import Book;
import Patron;
import Library;
using namespace Chrono;

int main()
{
	try {
		Book b1{"0-356-51700-4",
			"The Eye of the World",
			"Robert Jordan",
			Book::Genre::fiction,
			Date{Year{2021}, Month::sep, 16}};

		Book b2{"0-356-51700-4",
			"",
			"",
			Book::Genre::unspecified,
			Date{Year{1}, Month::jan, 1}};

		Patron p1{"Einstein", 1, 5.0};
		Patron p2{"Newton", 2, 0.0};
		Patron p3{"Newton2", 2, 0.0};

		Library l;
		l.add_book(b1);
		//l.add_book(b2); //throws exception, book already exists
		l.add_patron(p1);
		l.add_patron(p2);
		//l.add_patron(p3); //throws exception, patron already exists

		l.check_out(b1, p1); //returns false because p1 owes fees
		std::cout << l.transactions().size() << '\n';
		l.check_out(b1, p2);
		std::cout << l.transactions().size() << '\n';

		std::vector<Patron> v = patrons_with_fees(l);
		std::cout << "\nPatrons with fees:\n";
		for (const Patron& x : v)
			std::cout << x;
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
