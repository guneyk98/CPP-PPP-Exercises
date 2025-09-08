import std;
import Chrono;
import Book;

int main()
{
	try {
		Book b1{"0-356-51700-4", "The Eye of the World", "Robert Jordan", Book::Genre::fiction, Chrono::Date{Chrono::Year{2021}, Chrono::Month::sep, 16}};
		std::cout << b1;

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
