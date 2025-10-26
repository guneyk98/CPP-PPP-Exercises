#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex10");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point c{win.x_max()/2, win.y_max()/2};

	constexpr double r = 150;
	Circle circle{c, std::lround(r)};
	Mark m{c, 'x'};

	win.attach(circle);
	win.attach(m);

	double t = 0;
	for (;;) {
		const int x = std::lround(r*std::cos(t));
		const int y = std::lround(r*std::sin(t));
		m.move(c.x+x-m.point(0).x, c.y+y-m.point(0).y);
		win.wait_for_button();
		t += pi/8.0;
		if (t > 2.0*pi)
			t = 0;
	}
}
