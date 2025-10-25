#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Regular_polygon : Shape {
	Regular_polygon(Point centre, int num_sides, double radius);
	void draw_specifics(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex08");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Regular_polygon poly{{win.x_max()/2, win.y_max()/2}, 10, 250};
	poly.set_fill_color(Color::red);
	win.attach(poly);

	win.wait_for_button();
}

Regular_polygon::Regular_polygon(Point centre, int num_sides, double radius)
{
	if (num_sides <= 2)
		error("num_sides must be >2");

	const double theta = 2.0*pi/num_sides;
	for (int i = 0; i < num_sides; ++i) {
		const int x = centre.x + std::lround(radius * std::cos(i*theta));
		const int y = centre.y + std::lround(radius * std::sin(i*theta));
		add({x,	y});
	}
}

void Regular_polygon::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
