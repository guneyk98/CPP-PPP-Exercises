#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Striped_circle : Circle {
	Striped_circle(Point p, int rr);
	void set_fill_color(Color col) { hlines.set_color(col); redraw(); }
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	Lines hlines;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex06");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point centre{win.x_max()/2, win.y_max()/2};
	Striped_circle r{centre, 300};
	win.attach(r);
	win.wait_for_button();

	r.set_fill_color(Color::red);
	win.wait_for_button();
}

Striped_circle::Striped_circle(Point p, int rr)
	: Circle{p, rr}
{
	hlines.set_color(Color::invisible);
	for (int y = p.y - rr; y < p.y + rr; y+=2) {
		const int dx = std::lround(std::sqrt(rr*rr - (y-p.y)*(y-p.y)));
		hlines.add({p.x - dx, y}, {p.x + dx, y});
	}
}

void Striped_circle::draw_specifics(Painter& painter) const
{
	//draw the lines first so that the circle is drawn on top
	painter.set_line_style(hlines.style());
	painter.set_color(hlines.color());
	hlines.draw_specifics(painter);

	painter.set_line_style(this->style());
	painter.set_color(this->color());
	Circle::draw_specifics(painter);
}

void Striped_circle::move(int dx, int dy)
{
	Circle::move(dx, dy);
	hlines.move(dx, dy);
}
