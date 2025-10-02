import std;

struct number {
	int n;
	size_t count = 1;
};

bool number_exists(const std::vector<number>& v, int n, size_t& idx)
{
	for (size_t i = 0; i < v.size(); ++i) {
		if (n == v[i].n) {
			idx = i;
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const number& num)
{
	return os << num.n << (num.count>1 ? std::format("\t{}", num.count) : "");
}

bool operator<(const number& lhs, const number& rhs)
{
	return lhs.n < rhs.n;
}

int main()
{
	try {
		const std::string filename = "input.txt";
		std::ifstream ifs(filename);
		if (!ifs)
			throw std::runtime_error{std::format("couldn't open file {}", filename)};

		std::vector<number> nums;
		for (int n; ifs >> n;) {
			size_t idx;
			if (number_exists(nums, n, idx))
				++nums[idx].count;
			else
				nums.push_back(number{n});
		}
		std::sort(nums.begin(), nums.end());

		for (const number& n : nums)
			std::cout << n << '\n';
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
