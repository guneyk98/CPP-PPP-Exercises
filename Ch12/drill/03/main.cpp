#include <iostream>

class B1 {
public:
	virtual void vf() { std::cout <<  "B1::vf\n"; }
	void f() { std::cout <<  "B1::f\n"; }
};

class D1 : public B1 {
public:
	virtual void vf() override { std::cout <<  "D1::vf\n"; }
};

int main()
{
	B1 b1;
	b1.vf();		//B1::vf
	b1.f();			//B1::f

	D1 d1;
	d1.vf();		//D1::vf
	d1.f();			//B1::f

	B1& b1r{d1};
	b1r.vf();		//D1::vf
	b1r.f();		//B1::f
}
