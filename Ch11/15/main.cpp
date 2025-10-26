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
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex15");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr double r = 30;

	int colour_index = 0;

	Vector_ref<Regular_hexagon> hexs;
	const double x_dis = 3.0/2.0 * r;
	const double y_dis = std::sqrt(3.0) * r;
	for (int j = 0; j < 1+std::lround(win.y_max()/y_dis); ++j) {
		for (int i = 0; i < 1+std::lround(win.x_max()/x_dis); ++i) {
			const int x = std::lround(i*x_dis);
			const int y = std::lround((j+(i%2)/2.0)*y_dis);

			hexs.push_back(make_unique<Regular_hexagon>(Point{x, y}, r));
			hexs[hexs.size()-1].set_fill_color(colour_index);
			win.attach(hexs[hexs.size()-1]);
			++colour_index;
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
