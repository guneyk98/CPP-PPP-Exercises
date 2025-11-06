#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Rounded : Shape {
	Rounded(Point p, int ww, int hh, int corner_r);
	void draw_specifics(Painter& painter) const override;
private:
	int w, h;
	Vector_ref<Arc> arcs;
	Lines lines;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex09");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Rounded r{{50, 50}, 600, 300, 30};
	win.attach(r);
	win.wait_for_button();
}

Rounded::Rounded(Point p, int ww, int hh, int corner_r)	: w{ww}, h{hh}
{
	const int r = corner_r;

	const std::array<Point, 4> arc_pos{
		Point{p.x + r,	 p.y + r},		//top left
		Point{p.x + w-r, p.y + r},		//top right
		Point{p.x + w-r, p.y + h-r},	//bottom right
		Point{p.x + r,	 p.y + h-r}		//bottom left
	};
	constexpr std::array<int, 4> arc_angle{90, 0, 270, 180};

	for (int i = 0; i < 4; ++i)
		arcs.push_back(make_unique<Arc>(arc_pos[i], r, r, arc_angle[i], 90));

	lines.add({p.x + r,	p.y}, {p.x + w-r, p.y});
	lines.add({p.x + w,	p.y + r}, {p.x + w,	p.y + h-r});
	lines.add({p.x + w-r, p.y + h}, {p.x + r, p.y + h});
	lines.add({p.x,	p.y + h-r}, {p.x, p.y + r});
}

void Rounded::draw_specifics(Painter& painter) const
{
	for (int i = 0; i < arcs.size(); ++i) {
		arcs[i].draw_specifics(painter);
	}
	lines.draw_specifics(painter);
}
