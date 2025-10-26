#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Right_triangle : Shape {
	Right_triangle(Point p, int x, int y);
	void draw_specifics(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex12");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr int size = 100;
	const Point c{win.x_max()/2, win.y_max()/2};

	const Point p1{c.x+size/2, c.y-size/2};

	Right_triangle t1{{p1.x, p1.y-size}, -size, size};
	Right_triangle t2{p1, size, -size};
	Right_triangle t3{{p1.x+size, p1.y}, -size, size};
	
	const Point p2{c.x-size/2, c.y+size/2};

	Right_triangle t4{{p2.x-size, p2.y}, size, -size};
	Right_triangle t5{p2, -size, size};
	Right_triangle t6{{p2.x, p2.y+size}, size, -size};

	const Point p3{c.x-size/2, c.y-size/2};
	Right_triangle t7{p3, -size, -size};

	const Point p4{c.x+size/2, c.y+size/2};
	Right_triangle t8{p4, size, size};

	t1.set_fill_color(Color::black);
	t2.set_fill_color(Color::blue);
	t3.set_fill_color(Color::cyan);
	t4.set_fill_color(Color::red);
	t5.set_fill_color(Color::green);
	t6.set_fill_color(Color::yellow);
	t7.set_fill_color(Color::magenta);
	t8.set_fill_color(Color::dark_red);

	win.attach(t1);
	win.attach(t2);
	win.attach(t3);
	win.attach(t4);
	win.attach(t5);
	win.attach(t6);
	win.attach(t7);
	win.attach(t8);
	win.wait_for_button();
}

Right_triangle::Right_triangle(Point p, int dx, int dy)
{
	add(p);
	add({p.x+dx, p.y});
	add({p.x, p.y+dy});
}

void Right_triangle::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
