import std;

//probably won't work well for large files
void reverse_char(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs)
		throw std::runtime_error{std::format("couldn't open file {}", filename)};

	const std::string outfilename = std::format("{}.rev", filename);
	std::ofstream ofs(outfilename);
	if (!ofs)
		throw std::runtime_error{std::format("couldn't open file {}", outfilename)};

	std::ostringstream buffer;
	buffer << ifs.rdbuf();

	for (int i = buffer.str().size()-1; i >= 0; --i)
		ofs << buffer.str()[i];
}

int main()
{
	try {
		reverse_char("input.txt");
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

