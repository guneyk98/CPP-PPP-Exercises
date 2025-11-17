#include <iostream>

int fac_rec(int n)
{
	return n>1 ? n*fac_rec(n-1) : 1;
}

int fac_ite(int n)
{
	int r = 1;
	while (n>1) {
		r *= n;
		--n;
	}
	return r;
}

int main()
{
	for (int i = 0; i <= 20; ++i) {
		const int rec = fac_rec(i);
		const int ite = fac_ite(i);
		
		std::cout << i << "!\trec: " << rec << "\tite: " << ite <<
			"\t" << (rec == ite ? "equal" : "not equal") << '\n';
	}
}
