#include <iostream>

class B1 {
public:
	virtual void vf() { std::cout <<  "B1::vf\n"; }
	void f() { std::cout <<  "B1::f\n"; }
	virtual void pvf() = 0;
};

class D1 : public B1 {
public:
	virtual void vf() override { std::cout <<  "D1::vf\n"; }
	void f() { std::cout <<  "D1::f\n"; }
};

class D2 : public D1 {
public:
	virtual void pvf() { std::cout << "D2::pvf\n"; }
};

int main()
{
	D2 d2; 
	d2.vf();		//D1::vf
	d2.f();			//D1::f
	d2.pvf();		//D2::f
}
