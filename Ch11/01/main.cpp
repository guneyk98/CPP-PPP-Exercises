#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Arrow : Shape {
	Arrow(Point p1, Point p2, double len = 20.0, double theta = pi/6.0);
	void draw_specifics(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch11 Ex01");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Arrow a1{{100,100}, {400, 400}};
	Arrow a2{{700,50}, {700, 100}, 10};
	Arrow a3{{300,200}, {500, 200}, 40, pi/4.0};

	a2.set_style(Line_style(Line_style::dash));
	a3.set_style(Line_style(Line_style::solid, 10));

	win.attach(a1);
	win.attach(a2);
	win.attach(a3);

	win.wait_for_button();
}

Arrow::Arrow(Point p1, Point p2, double len, double theta)
{
	add(p1);
	add(p2);

	double x21 = p1.x - p2.x;
	double y21 = p1.y - p2.y;
	const double mag = std::sqrt(x21*x21 + y21*y21);
	x21 /= mag; //normalise
	y21 /= mag;

	const double costheta = std::cos(theta);
	const double sintheta = std::sin(theta);

	//2D rotation matrix
	const int x23 = std::lround(len*(x21*costheta - y21*sintheta));
	const int y23 = std::lround(len*(x21*sintheta + y21*costheta));
	const int x24 = std::lround(len*(x21*costheta + y21*sintheta));
	const int y24 = std::lround(len*(-x21*sintheta + y21*costheta));

	add({p2.x+x23, p2.y+y23});
	add({p2.x+x24, p2.y+y24});
}

void Arrow::draw_specifics(Painter& painter) const
{
	painter.draw_line(point(0), point(1));
	painter.draw_line(point(1), point(2));
	painter.draw_line(point(1), point(3));
}
