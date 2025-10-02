import std;

//probably won't work well for large files
void reverse_word(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs)
		throw std::runtime_error{std::format("couldn't open file {}", filename)};

	const std::string outfilename = std::format("{}.rev", filename);
	std::ofstream ofs(outfilename);
	if (!ofs)
		throw std::runtime_error{std::format("couldn't open file {}", outfilename)};

	std::vector<std::vector<std::string>> lines;
	for (std::string line; std::getline(ifs, line);) {
		std::vector<std::string> words;
		std::istringstream iss{line};
		for (std::string word; iss >> word;)
			words.push_back(word);
		lines.push_back(words);
	}
	
	for (int i = lines.size()-1; i >= 0; --i) {
		for (int j = lines[i].size()-1; j >= 0; --j)
			ofs << lines[i][j] << ' ';
		ofs << '\n';
	}
}

int main()
{
	try {
		reverse_word("input.txt");
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
