#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Rounded_box : Shape {
	Rounded_box(Point p, int ww, int hh);
	void draw_specifics(Painter& painter) const override;
private:
	Rectangle rect;
	Vector_ref<Arc> arcs;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex18");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point c{win.x_max()/2, win.y_max()/2};
	int box_w = 300;
	int box_h = 200;

	Rounded_box box{{c.x - box_w/2, c.y - box_h/2}, box_w, box_h};
	win.attach(box);
	win.wait_for_button();
}

Rounded_box::Rounded_box(Point p, int ww, int hh)
	: rect{p, ww, hh}
{
	arcs.push_back(make_unique<Arc>(
		Point{p.x + rect.width()/4, p.y + rect.height()/4},
		rect.width()/4,
		rect.height()/4,
		90,
		90
	));
	arcs.push_back(make_unique<Arc>(
		Point{p.x + (3*rect.width())/4, p.y + rect.height()/4},
		rect.width()/4,
		rect.height()/4,
		0,
		90
	));
	arcs.push_back(make_unique<Arc>(
		Point{p.x + (3*rect.width())/4, p.y + (3*rect.height())/4},
		rect.width()/4,
		rect.height()/4,
		270,
		90
	));
	arcs.push_back(make_unique<Arc>(
		Point{p.x + rect.width()/4, p.y + (3*rect.height())/4},
		rect.width()/4,
		rect.height()/4,
		180,
		90
	));

	add({p.x + rect.width()/4, p.y});
	add({p.x + (3*rect.width()/4), p.y});

	add({p.x + rect.width()/4, p.y + rect.height()});
	add({p.x + (3*rect.width()/4), p.y + rect.height()});

	add({p.x, p.y + rect.height()/4});
	add({p.x, p.y + (3*rect.height())/4});

	add({p.x + rect.width(), p.y + rect.height()/4});
	add({p.x + rect.width(), p.y + (3*rect.height())/4});
}

void Rounded_box::draw_specifics(Painter& painter) const
{
	for (int i = 0; i < arcs.size(); ++i) {
		arcs[i].draw_specifics(painter);
	}
	for (int i = 1; i < number_of_points(); i += 2)
		painter.draw_line(point(i-1), point(i));
}
