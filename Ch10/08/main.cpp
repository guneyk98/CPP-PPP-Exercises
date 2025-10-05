#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	Application app;

	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex08");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	//boundary
	const int bx_min = win.x_max()/10;
	const int bx_max = (9*win.x_max())/10;
	const int by_min = win.y_max()/10;
	const int by_max = (9*win.y_max())/10;
	const int b_w = bx_max-bx_min;
	[[maybe_unused]] const int b_h = by_max-by_min;

	//b_w = 6*r + 2*g
	//r/g = ratio = 4
	//(6*ratio + 2)*g = b_w

	//horizontal gap/radius
	const int ratio = 3;
	const int gap = b_w/(6*ratio + 2);
	const int rad = gap*ratio;

	const Point p1{bx_min+rad, (by_max+by_min)/2 - rad/2};
	Circle c1{p1, rad};
	Circle c2{Point{p1.x + gap + 2*rad, p1.y}, rad};
	Circle c3{Point{p1.x + 2*gap + 4*rad, p1.y}, rad};

	const Point p2{p1.x+rad+gap/2, (by_max+by_min)/2 + rad/2};
	Circle c4{p2, rad};
	Circle c5{Point{p2.x + gap + 2*rad, p2.y}, rad};

	c1.set_color(Color::blue);
	c2.set_color(Color::black);
	c3.set_color(Color::red);
	c4.set_color(Color::yellow);
	c5.set_color(Color::green);

	c1.set_style(Line_style(Line_style::solid, 12));
	c2.set_style(Line_style(Line_style::solid, 12));
	c3.set_style(Line_style(Line_style::solid, 12));
	c4.set_style(Line_style(Line_style::solid, 12));
	c5.set_style(Line_style(Line_style::solid, 12));

	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(c4);
	win.attach(c5);
	win.wait_for_button();

}
