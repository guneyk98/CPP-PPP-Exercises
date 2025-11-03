#include <iostream>

class B1 {
public:
	virtual void vf() { std::cout <<  "B1::vf\n"; }
	void f() { std::cout <<  "B1::f\n"; }
};

class D1 : public B1 {
public:
	virtual void vf() override { std::cout <<  "D1::vf\n"; }
	void f() { std::cout <<  "D1::f\n"; }
};

int main()
{
	B1 b1;
	b1.vf();		//B1::vf
	b1.f();			//B1::f

	D1 d1;
	d1.vf();		//D1::vf
	d1.f();			//D1::f

	B1& b1r{d1};
	b1r.vf();		//D1::vf
	b1r.f();		//B1::f

	/*
	For virtual functions the vtable pointer determines which function
	is called, which is determined by the underlying type of the object.
	For normal functions, it's the type of the reference/pointer that
	determines which function is called.
	*/
}
