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
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex13");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr int size = 20;

	Vector_ref<Right_triangle> tris;
	for (int j = 0; j < win.y_max()/size; ++j) {
		for (int i = 0; i < win.x_max()/size; ++i) {
			tris.push_back(make_unique<Right_triangle>(Point{i*size, j*size}, size, size));
			tris[tris.size()-1].set_fill_color(Color::green);
			win.attach(tris[tris.size()-1]);
			tris.push_back(make_unique<Right_triangle>(Point{i*size+size, j*size+size}, -size, -size));
			tris[tris.size()-1].set_fill_color(Color::red);
			win.attach(tris[tris.size()-1]);
		}
	}
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
