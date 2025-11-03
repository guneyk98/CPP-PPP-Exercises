#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Rounded : Shape {
	Rounded(Point p, int ww, int hh);
	void draw_specifics(Painter& painter) const override;
private:
	Rectangle rect;
	Vector_ref<Arc> arcs;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex09");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point c{win.x_max()/2, win.y_max()/2};
	int box_w = 300;
	int box_h = 200;

	Rounded r{{c.x - box_w/2, c.y - box_h/2}, box_w, box_h};
	win.attach(r);
	win.wait_for_button();
}

Rounded::Rounded(Point p, int ww, int hh)
	: rect{p, ww, hh}
{
	const int w = rect.width();
	const int h = rect.height();

	const std::array<Point, 4> arc_pos{
		Point{p.x + w/4,	 p.y + h/4},		//top left
		Point{p.x + (3*w)/4, p.y + h/4 },		//top right
		Point{p.x + (3*w)/4, p.y + (3*h)/4},	//bottom right
		Point{p.x + w/4,	 p.y + (3*h)/4}		//bottom left
	};
	constexpr std::array<int, 4> arc_angle{90, 0, 270, 180};
	
	for (int i = 0; i < 4; ++i)
		arcs.push_back(make_unique<Arc>(arc_pos[i], w/4, h/4, arc_angle[i], 90));

	add({p.x + w/4, p.y});
	add({p.x + (3*w)/4, p.y});

	add({p.x + w/4, p.y + h});
	add({p.x + (3*w)/4, p.y + h});

	add({p.x, p.y + h/4});
	add({p.x, p.y + (3*h)/4});

	add({p.x + w, p.y + h/4});
	add({p.x + w, p.y + (3*h)/4});
}

void Rounded::draw_specifics(Painter& painter) const
{
	for (int i = 0; i < arcs.size(); ++i) {
		arcs[i].draw_specifics(painter);
	}
	for (int i = 1; i < number_of_points(); i += 2)
		painter.draw_line(point(i-1), point(i));
}
