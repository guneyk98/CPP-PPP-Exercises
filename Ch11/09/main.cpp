#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex09");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point c{win.x_max()/2, win.y_max()/2};

	Ellipse ellipse{c, 150, 100};

	Axis x_axis{Axis::x, {c.x-200, c.y}, 400, 0, "x"};
	Axis y_axis{Axis::y, {c.x, c.y+150}, 300, 0, "y"};

	Mark m1{ellipse.focus1(), '1'};
	Mark m2{ellipse.focus2(), '2'};

	Point p{c.x+75, c.y-87};
	Mark mp{p, 'x'};
	Line l1{ellipse.focus1(), p};
	Line l2{ellipse.focus2(), p};

	win.attach(ellipse);
	win.attach(x_axis);
	win.attach(y_axis);
	win.attach(m1);
	win.attach(m2);
	win.attach(mp);
	win.attach(l1);
	win.attach(l2);

	win.wait_for_button();
}
