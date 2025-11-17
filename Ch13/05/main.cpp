#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

double leibniz(int n)
{
	double x = 1.0;
	for (int i = 1; i < n; ++i)
		x += (i%2 ? -1.0 : 1.0)/(2.0*i + 1.0);
	return x;
}

int main()
{
	constexpr int xmax = 600;
	constexpr int ymax = 600;

	constexpr int xlength = 500;
	constexpr int ylength = 500;

	constexpr int xoffset = (xmax-xlength)/2;
	constexpr int yoffset = (ymax-ylength)/2;

	constexpr Point c{xmax/2, ymax/2};

	constexpr double r1 = 0;
	constexpr double r2 = 100;
	constexpr double xscale = xlength/(r2-r1);
	constexpr double yscale = ylength/4.0;

	Application app;
	Simple_window win({0, 0}, xmax, ymax, "Ch13 Ex05");
	//fill background white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Axis ax{Axis::x, {xoffset, c.y}, xlength, 8, "x"};
	Axis ay{Axis::y, {c.x, ymax-yoffset}, ylength, 8};

	win.attach(ax);
	win.attach(ay);
	
	for (int i = 1; i <= 32; ++i) {
		const double y = leibniz(i);
		std::cout << 4*y << '\n';
		Function f{[y](double) { return y; } , r1, r2, c, xlength, xscale, yscale};
		win.attach(f);
		win.wait_for_button();
		win.detach(f);
	}
}
