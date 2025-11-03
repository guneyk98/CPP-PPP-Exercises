#include <iostream>

class B2 {
public:
	virtual void pvf() = 0;
};

class D21 : public B2 {
public:
	D21(std::string ss) : s(ss) {}
	virtual void pvf() { std::cout << s << '\n'; }
private:
	std::string s;
};

class D22 : public B2 {
public:
	D22(int ii) : i(ii) {}
	virtual void pvf() { std::cout << i << '\n'; }
private:
	int i;
};

void f(B2& b2)
{
	b2.pvf();
}

int main()
{
	D21 d21("D21");
	D22 d22(22);

	d21.pvf();
	d22.pvf();
}
