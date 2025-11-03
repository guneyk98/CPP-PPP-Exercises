#include <iostream>

class A {
public:
	virtual void vf() = 0;
};

int main()
{
	A a; //error C2259: 'A': cannot instantiate abstract class
}
