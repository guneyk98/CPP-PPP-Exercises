#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Right_triangle : Shape {
	Right_triangle(Point p, double dx, double dy, double rot);
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

	constexpr double tri_w = 100.0;
	const double small_tri_w = std::sqrt(0.5*tri_w*tri_w);
	const double pent_w = 2.0*small_tri_w + tri_w;

	const Point c{win.x_max()/2, win.y_max()/2};
	Mark m{c, 'x'};
	win.attach(m);

	const int len_large = std::lround(pent_w/2.0);
	const int len_small = std::lround(tri_w/2.0);

	//offset from centre to right-angles
	std::array<std::array<int, 2>, 8> offsets{{
		{+len_small, -len_large},
		{+len_large, -len_small},
		{+len_large, +len_small},
		{+len_small, +len_large},
		{-len_small, +len_large},
		{-len_large, +len_small},
		{-len_large, -len_small},
		{-len_small, -len_large},
	}};

	double theta = pi/2.0;
	int colour_index = 0;
	Vector_ref<Right_triangle> tris;
	for (int i = 0; i < offsets.size(); ++i) {
		const int x = c.x + offsets[i][0];
		const int y = c.y + offsets[i][1];
		tris.push_back(make_unique<Right_triangle>(Point{x, y}, tri_w, tri_w, theta));
		tris[tris.size()-1].set_fill_color(colour_index);
		win.attach(tris[tris.size()-1]);

		++colour_index;
		theta += pi/4.0;
	}

	win.wait_for_button();
}

Right_triangle::Right_triangle(Point p, double dx, double dy, double rot)
{
	add(p);
	const double cost = std::cos(rot);
	const double sint = std::sin(rot);
	add({p.x + std::lround(dx*cost-sint), p.y + std::lround(dx*sint+cost)});
	add({p.x + std::lround(cost-dy*sint), p.y + std::lround(sint+dy*cost)});
}

void Right_triangle::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}
