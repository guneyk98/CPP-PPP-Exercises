#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

constexpr double pi = numbers::pi_v<double>;

double npoly_radius(int n, double s)
{
	return s/(2.0*std::sin(pi/n));
}

void construct_npoly(Closed_polyline& poly, Point p, int n, double s)
{
	const double r = npoly_radius(n, s);
	for (int i = 0; i < n; ++i) {
		const double azimuth = i * 2.0*pi/n;
		const double theta = pi/2.0 - azimuth;

		const double x = r*std::cos(theta);
		const double y = r*std::sin(theta);

		poly.add(Point{p.x + std::lround(x), p.y + std::lround(r-y)});
	}
}

int main()
{
	using namespace Graph_lib;
	Application app;

	constexpr int win_x = 0, win_y = 0;
	constexpr int win_w = 1920, win_h = 1080;

	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex11");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	const Point p{win_w/2, 50};
	constexpr int side_length = 200;
	constexpr int num_poly = 10;

	std::array<Closed_polyline, num_poly> npoly;
	for (int i = 0; i < num_poly; ++i) {
		construct_npoly(npoly[i], p, i+3, side_length);
		win.attach(npoly[i]);
	}
	win.wait_for_button();
}
