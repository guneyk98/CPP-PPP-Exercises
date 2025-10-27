#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Star : Shape {
	Star(Point p, int num_points, double inner_len, double outer_len);
	void draw_specifics(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex17");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point c{win.x_max()/2, win.y_max()/2};

	Star star1{c, 5, 150, 300};
	win.attach(star1);
	win.wait_for_button();
	win.detach(star1);

	Star star2{c, 8, 150, 300};
	win.attach(star2);
	win.wait_for_button();
}

Star::Star(Point p, int num_points, double inner_len, double outer_len)
{
	if (num_points <= 2)
		error("num_sides must be >2");

	for (int i = 0; i < num_points; ++i) {
		const double theta = 2.0*pi/num_points;
		add(Point{
			p.x + std::lround(inner_len * std::cos(i*theta)),
			p.y + std::lround(inner_len * std::sin(i*theta))
		});
		add(Point{
			p.x + std::lround(outer_len * std::cos(i*theta + pi/num_points)),
			p.y + std::lround(outer_len * std::sin(i*theta + pi/num_points))
		});
	}
}

void Star::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
