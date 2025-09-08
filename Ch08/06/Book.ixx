export module Book;

import std;
import Chrono;

export class Book {
public:
	Book(std::string isbn, std::string title, std::string author, Chrono::Date copyright, bool checked_out = false);

	const std::string& isbn() const { return _isbn; }
	const std::string& title() const { return _title; }
	const std::string& author() const { return _author; }
	const Chrono::Date& copyright() const { return _copyright; }
	bool is_checked_out() const { return checked_out; }

	void check_in();
	void check_out();
private:
	std::string _isbn;
	std::string _title;
	std::string _author;
	Chrono::Date _copyright;
	bool checked_out;
};

bool is_valid_isbn(const std::string& isbn);

export std::ostream& operator<<(std::ostream& os, const Book& b);
export bool operator==(const Book& lhs, const Book& rhs);
export bool operator!=(const Book& lhs, const Book& rhs);

//Implementation

Book::Book(std::string isbn, std::string title, std::string author, Chrono::Date copyright, bool checked_out)
	: _isbn{isbn}, _title{title}, _author{author}, _copyright{copyright}, checked_out{checked_out}
{
	if (!is_valid_isbn(isbn))
		throw std::runtime_error{"Invalid isbn"};
}

void Book::check_in()
{
	if (!is_checked_out())
		throw std::runtime_error{"Can't check book in; it's not checked out"};
	checked_out = false;
}

void Book::check_out()
{
	if (is_checked_out())
		throw std::runtime_error{"Can't check book out; it's already checked out"};
	checked_out = true;
}

bool is_valid_isbn(const std::string& isbn)
{
	size_t i = 0;
	for (size_t part = 0; part < 3; ++part) {
		if (i == isbn.size() || !std::isdigit(static_cast<unsigned char>(isbn[i]))) //first char must be digit
			return false;
		while (i != isbn.size() && std::isdigit(static_cast<unsigned char>(isbn[i]))) //skip consecutive digits
			++i;
		if (i == isbn.size() || isbn[i] != '-') //next character must be hyphen
			return false;
		++i;
	}
	return i == isbn.size()-1 && std::isalnum(static_cast<unsigned char>(isbn[i])); //final character is alpha-numeric
}

std::ostream& operator<<(std::ostream& os, const Book& b)
{
	return os <<
		"ISBN: " << b.isbn() << '\n' <<
		"Title: " << b.title() << '\n' <<
		"Author: " << b.author() << '\n' <<
		"Copyright Date: " << b.copyright() << '\n' <<
		"Checked out: " << b.is_checked_out() << '\n';
}

bool operator==(const Book& lhs, const Book& rhs)
{
	return lhs.isbn() == rhs.isbn();
}

bool operator!=(const Book& lhs, const Book& rhs)
{
	return !(lhs==rhs);
}
