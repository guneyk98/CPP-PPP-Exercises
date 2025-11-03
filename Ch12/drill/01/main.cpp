#include <iostream>

class B1 {
public:
	virtual void vf() { std::cout <<  "B1::vf\n"; }
	void f() { std::cout <<  "B1::f\n"; }
};

int main()
{
	B1 b1;
	b1.vf(); //B1::vf
	b1.f();  //B1::f
}
