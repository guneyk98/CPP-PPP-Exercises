import std;
import Chrono;
import Book;

int main()
{
	try {
		Book b1{"0-356-51700-4", "The Eye of the World", "Robert Jordan", Chrono::Date{Chrono::Year{2021}, Chrono::Month::sep, 16}};
		std::cout <<
			"ISBN: " << b1.isbn() << '\n' <<
			"Title: " << b1.title() << '\n' <<
			"Author: " << b1.author() << '\n' <<
			"Copyright Date: " << b1.copyright() << '\n' <<
			"Checked out: " << (b1.is_checked_out() ? "true" : "false") << '\n';

		b1.check_out();
		std::cout << "Checked out: " << (b1.is_checked_out() ? "true" : "false") << '\n';
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
