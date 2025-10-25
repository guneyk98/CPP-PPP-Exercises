#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Regular_hexagon : Shape {
	Regular_hexagon(Point centre, double radius);
	void draw_specifics(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex06");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Regular_hexagon hex{{win.x_max()/2, win.y_max()/2}, 250};
	hex.set_fill_color(Color::red);
	win.attach(hex);

	win.wait_for_button();
}

Regular_hexagon::Regular_hexagon(Point centre, double radius)
{
	for (int i = 0; i < 6; ++i) {
		const int x = centre.x + static_cast<int>(radius * std::cos(i*pi/3));
		const int y = centre.y + static_cast<int>(radius * std::sin(i*pi/3));
		add({x,	y});
	}
}

void Regular_hexagon::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
