#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <numbers>

constexpr double pi = numbers::pi_v<double>;
using namespace Graph_lib;

int main()
{
	constexpr int xmax = 600;
	constexpr int ymax = 600;

	constexpr int xlength = 500;
	constexpr int ylength = 500;

	constexpr int xoffset = (xmax-xlength)/2;
	constexpr int yoffset = (ymax-ylength)/2;

	constexpr Point c{xmax/2, ymax/2};

	constexpr double r1 = -2.0*pi;
	constexpr double r2 = 2.0*pi;
	constexpr double xscale = xlength/(r2-r1);
	constexpr double yscale = ylength/4.0;

	Application app;
	Simple_window win({0, 0}, xmax, ymax, "Ch13 Ex04");
	//fill background white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Axis x{Axis::x, {xoffset, c.y}, xlength, 8, "x"};
	Axis y{Axis::y, {c.x, ymax-yoffset}, ylength, 8};

	Function f1{[](double x) { return sin(x); }, r1, r2, c, xlength, xscale, yscale};
	Function f2{[](double x) { return cos(x); }, r1, r2, c, ylength, xscale, yscale};
	Function f3{[](double x) { return sin(x)+cos(x); }, r1, r2, c, ylength, xscale, yscale};
	Function f4{[](double x) { return sin(x)*sin(x)+cos(x)*cos(x); } , -2.0*pi, 2.0*pi, c, ylength, xscale, yscale};
	
	
	f1.set_color(Color::blue);
	f2.set_color(Color::green);
	f3.set_color(Color::red);
	f4.set_color(Color::magenta);

	Text t1{{c.x+60, c.y-150}, "sin(x)"};
	Text t2{{c.x-65, c.y-150}, "cos(x)"};
	Text t3{{c.x, c.y-200}, "sin(x)+cos(x)"};
	Text t4{{c.x+130, c.y-120}, "sin2(x)+cos2(x)"};

	t1.set_color(Color::blue);
	t2.set_color(Color::green);
	t3.set_color(Color::red);
	t4.set_color(Color::magenta);

	Text tx1{{c.x-270, c.y-25}, "-2pi"};
	Text tx2{{c.x+240, c.y-25}, "2pi"};
	Text ty1{{c.x+5, c.y+240}, "-2"};
	Text ty2{{c.x+5, c.y-250}, "2"};

	win.attach(x);
	win.attach(y);
	win.attach(f1);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);
	win.attach(t1);
	win.attach(t2);
	win.attach(t3);
	win.attach(t4);
	win.attach(tx1);
	win.attach(tx2);
	win.attach(ty1);
	win.attach(ty2);
	win.wait_for_button();
}
