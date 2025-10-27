#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Poly : Polygon {
	Poly(std::initializer_list<Point> points);
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex16");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Poly poly{
		{300, 50},
		{400, 225},
		{650, 275},
		{275, 425},
		{150, 350},
	};

	win.attach(poly);
	win.wait_for_button();
}

Poly::Poly(std::initializer_list<Point> points)
{
	if (points.size() < 3)
		error("Poly must have at least 3 points");

	for (const Point& p : points)
		Polygon::add(p);
}