export module Library;

import std;
import Book;
import Chrono;
import Patron;

export class Library {
public:
	struct Transaction {
		Book b;
		Patron p;
		Chrono::Date d;
	};

	const std::vector<Book>& books() const { return _books; }
	const std::vector<Patron>& patrons() const { return _patrons; }
	const std::vector<Transaction>& transactions() const { return _transactions; }

	void add_book(const Book& b);
	void add_patron(const Patron& p);
	bool check_out(const Book& b, const Patron& p);
private:
	std::vector<Book> _books;
	std::vector<Patron> _patrons;
	std::vector<Transaction> _transactions;
};

export bool book_exists(const Book& b, const Library& l);
export bool patron_exists(const Patron& p, const Library& l);
export std::vector<Patron> patrons_with_fees(const Library& l);

//Implementation

void Library::add_book(const Book& b)
{
	if (book_exists(b, *this))
		throw std::exception{"Book, with the same isbn, already exists in library"};
	_books.push_back(b);
}

void Library::add_patron(const Patron& p)
{
	if (patron_exists(p, *this))
		throw std::exception{"Patron, with the same card number, already exists in library"};
	_patrons.push_back(p);
}

bool Library::check_out(const Book& b, const Patron& p)
{
	if (!book_exists(b, *this)) {
		std::cerr << "Error: The book does not exist in the library.\n" << b;
		return false;
	}
	if (!patron_exists(p, *this)) {
		std::cerr << "Error: The patron does not exist in the library.\n" << p;
		return false;
	}
	if (patron_owes_fees(p)) {
		std::cerr << "Error: The patron owes fees.\n" << p;
		return false;
	}

	_transactions.push_back({
		b,
		p,
		Chrono::Date{Chrono::Year{2025}, Chrono::Month::sep, 9}});
	return true;
}

bool book_exists(const Book& b, const Library& l)
{
	const std::vector<Book>& books = l.books();
	for (const Book& x : books)
		if (x == b)
			return true;
	return false;
}

bool patron_exists(const Patron& p, const Library& l)
{
	const std::vector<Patron>& patrons = l.patrons();
	for (const Patron& x : patrons)
		if (x == p)
			return true;
	return false;
}

std::vector<Patron> patrons_with_fees(const Library& l)
{
	std::vector<Patron> res;
	const std::vector<Patron>& patrons = l.patrons();
	for (const Patron& x : patrons)
		if (patron_owes_fees(x))
			res.push_back(x);
	return res;
}
