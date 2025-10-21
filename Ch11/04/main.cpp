#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Box : Rectangle {
	Box(Point xy, int ww, int hh, const std::string& s)
		: Rectangle{xy, ww, hh}, label{{xy.x + 5, xy.y + 5}, s} {}

	void draw_specifics(Painter& painter) const override;
private:
	Text label;
};

struct Arrow : Shape {
	Arrow(Point p1, Point p2, double len = 10.0, double theta = pi/12.0);
	void draw_specifics(Painter& painter) const override;
};

Point n(const Rectangle& r);
Point s(const Rectangle& r);
Point e(const Rectangle& r);
Point w(const Rectangle& r);
Point centre(const Rectangle& r);
Point ne(const Rectangle& r);
Point se(const Rectangle& r);
Point sw(const Rectangle& r);
Point nw(const Rectangle& r);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch11 Ex04");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Box b1{{100, 100}, 150, 40, "Window"};
	Box b2{{325, 100}, 150, 40, "Line_style"};
	Box b3{{550, 100}, 150, 40, "Color"};

	Box b4{{100, 200}, 150, 40, "Simple_window"};
	Box b5{{325, 200}, 150, 40, "Shape"};
	Box b6{{550, 200}, 150, 40, "Point"};

	Box b7{{50, 300}, 75, 40, ""};
	Box b8{{155, 300}, 75, 40, "Lines"};
	Box b9{{260, 300}, 75, 40, "Polygon"};
	Box b10{{365, 300}, 75, 40, "Axis"};
	Box b11{{470, 300}, 75, 40, "Rectangle"};
	Box b12{{575, 300}, 75, 40, "Text"};
	Box b13{{680, 300}, 75, 40, "Image"};

	Arrow a1(n(b4), s(b1));
	Arrow a2(n(b7), s(b5));
	Arrow a3(n(b8), s(b5));
	Arrow a4(n(b9), s(b5));
	Arrow a5(n(b10), s(b5));
	Arrow a6(n(b11), s(b5));
	Arrow a7(n(b12), s(b5));
	Arrow a8(n(b13), s(b5));

	win.attach(b1);
	win.attach(b2);
	win.attach(b3);
	win.attach(b4);
	win.attach(b5);
	win.attach(b6);
	win.attach(b7);
	win.attach(b8);
	win.attach(b9);
	win.attach(b10);
	win.attach(b11);
	win.attach(b12);
	win.attach(b13);
	win.attach(a1);
	win.attach(a2);
	win.attach(a3);
	win.attach(a4);
	win.attach(a5);
	win.attach(a6);
	win.attach(a7);
	win.attach(a8);

	win.wait_for_button();
}

void Box::draw_specifics(Painter& painter) const
{
	Rectangle::draw_specifics(painter);
	label.draw_specifics(painter);
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

Point n(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y};
}

Point s(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y + r.height()};
}

Point e(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y + r.height()/2};
}

Point w(const Rectangle& r)
{
	return {r.point(0).x, r.point(0).y + r.height()/2};
}

Point centre(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y + r.height()/2};
}

Point ne(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y};
}

Point se(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y + r.height()};
}

Point sw(const Rectangle& r)
{
	return {r.point(0).x, r.point(0).y + r.height()};
}

Point nw(const Rectangle& r)
{
	return r.point(0);
}
