import std;
#include <cassert>

const std::array<const std::string, 8> word_contracted{
	"aren't",
	"can't",
	"couldn't",
	"don't",
	"won't",
	"i'll",
	"he'll",
	"she'll"
	//etc...
};

const std::array<const std::string, 8> word_expanded{
	"are not",
	"cannot",
	"could not",
	"do not",
	"will not",
	"i will",
	"he will",
	"she will"
	//etc...
};

std::string& modify_str(std::string& str);
bool is_punct(char ch);
bool is_alpha(char ch);
char to_lower(char ch);
//finds the start index and size of a word, given an index within the word.
void find_word(const std::string& str, size_t idx, size_t& start_idx, size_t& size);
bool is_contracted(const std::string& str, size_t& found_idx);

int main()
{
	try {
		for (std::string str; std::getline(std::cin, str);)
			std::cout << modify_str(str) << '\n';
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

std::string& modify_str(std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i) {
		str[i] = std::tolower(static_cast<unsigned char>(str[i]));

		if (str[i] == '"') {
			//look for end of quote
			for (size_t j = i+1; j < str.size(); ++j) {
				if (str[j] == '"')
					i = j; //skip if found
			}
		} else if (str[i] == '\'') {
			size_t start_idx, size;
			find_word(str, i, start_idx, size);

			size_t word_idx;
			if (is_contracted(std::string(str, start_idx, size), word_idx)) {
				str.replace(start_idx, size, word_expanded[word_idx]);
				i = start_idx+word_expanded[word_idx].size()-1;
			}
		} else if (is_punct(str[i])) {
			//ignore hyphenated words
			if (str[i] == '-' && i != 0 && i != str.size()-1 && is_alpha(str[i-1]) && is_alpha(str[i+1]))
				continue;
			str[i] = ' ';
		}
	}
	return str;
}

bool is_punct(char ch)
{
	return ch == '.' || ch == ';' ||ch == ',' ||ch == '?' ||ch == '-' ||ch == '\'';
}

char to_lower(char ch)
{
	return std::tolower(static_cast<unsigned char>(ch));
}

bool is_alpha(char ch)
{
	return std::isalpha(static_cast<unsigned char>(ch));
}

void find_word(const std::string& str, size_t idx, size_t& start_idx, size_t& size)
{
	assert(idx < str.size());

	start_idx = idx;
	size_t end_idx = idx+1;
	for (; start_idx && is_alpha(str[start_idx-1]); --start_idx)
		;
	for (; end_idx < str.size() && is_alpha(str[end_idx]); ++end_idx)
		;
	size = end_idx-start_idx;
}

bool is_contracted(const std::string& str, size_t& found_idx)
{
	for (size_t i = 0; i < word_contracted.size(); ++i) {
		const std::string& word = word_contracted[i];

		if (str.size() != word.size())
			continue;
		//case insensitive compare
		for (size_t j = 0; to_lower(str[j]) == word[j]; ++j) {
			if (j == str.size()) {
				found_idx = i;
				return true;
			}
		}
	}
	return false;
}