#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Scale {
	int cbase;
	int vbase;
	double scale;
public:
	Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} { }
	int operator()(double v) const { return std::lround(cbase+(v-vbase)*scale); }
};

double one(double) { return 1; }
double slope(double x) { return 0.5*x; }
double square(double x) { return x*x; }
double sloping_cos(double x) { return slope(x)+std::cos(x); }

int main()
{
	constexpr int xmax = 600;
	constexpr int ymax = 600;

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	constexpr int xoffset = (xmax-xlength)/2;
	constexpr int yoffset = (ymax-ylength)/2;

	constexpr Point c{xmax/2, ymax/2};

	constexpr double xscale = 20.0;
	constexpr double yscale = 20.0;

	Application app;
	Simple_window win({0, 0}, xmax, ymax, "Function graphs");
	//fill background white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Scale xs{xoffset, -10, xscale};
	Scale ys{ymax-yoffset, -10, -yscale};

	Axis x{Axis::x, {xoffset, c.y}, xlength, std::lround(xlength/xscale), "1 = 20 pixels"};
	Axis y{Axis::y, {c.x, ymax-yoffset}, ylength, std::lround(ylength/yscale), "1 = 20 pixels"};

	x.set_color(Color::red);
	y.set_color(Color::red);

	Function f1{one, -10, 11, c, xlength, xscale, yscale};
	Function f2{slope, -10, 11, c, ylength, xscale, yscale};
	Function f3{square, -10, 11, c, ylength, xscale, yscale};
	Function f4{[](double x) { return std::cos(x); } , -10, 11, c, ylength, xscale, yscale};
	Function f5{sloping_cos, -10, 11, c, ylength, xscale, yscale};

	f4.set_color(Color::blue);

	Text t1{Point{xs(-10.0), ys(slope(-10.0))}, "0.5x"};

	win.attach(x);
	win.attach(y);
	win.attach(f1);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);
	win.attach(f5);
	win.attach(t1);
	win.wait_for_button();
}
