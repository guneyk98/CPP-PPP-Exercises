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
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex07");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr double r = 30;
	constexpr int num_x = 8;
	constexpr int num_y = 8;
	constexpr Point p{100, 100};

	Vector_ref<Regular_hexagon> hexs;
	const double x_dis = 3.0/2.0 * r;
	const double y_dis = std::sqrt(3.0) * r;
	for (int j = 0; j < num_x; ++j) {
		for (int i = 0; i < num_y; ++i) {
			const int x = p.x + std::lround(i*x_dis);
			const int y = p.y + std::lround((j+(i%2)/2.0)*y_dis);
			hexs.push_back(make_unique<Regular_hexagon>(Point{x, y}, r));
			win.attach(hexs[hexs.size()-1]);
		}
	}
	win.wait_for_button();
}

Regular_hexagon::Regular_hexagon(Point centre, double radius)
{
	for (int i = 0; i < 6; ++i) {
		const int x = centre.x + std::lround(radius * std::cos(i*pi/3));
		const int y = centre.y + std::lround(radius * std::sin(i*pi/3));
		add({x,	y});
	}
}

void Regular_hexagon::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
