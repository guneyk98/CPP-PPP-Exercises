#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Striped_rectangle : Rectangle {
	Striped_rectangle(Point xy, int ww, int hh);
	void set_fill_color(Color col) { hlines.set_color(col); redraw(); }
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	Lines hlines;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex05");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Striped_rectangle r{{100, 100}, 300, 200};
	win.attach(r);
	win.wait_for_button();
	r.set_fill_color(Color::red);
	win.wait_for_button();
}

Striped_rectangle::Striped_rectangle(Point xy, int ww, int hh)
	: Rectangle{xy, ww, hh}
{
	hlines.set_color(Color::invisible);
	const int x1 = xy.x;
	const int x2 = xy.x + ww;
	for (int y = xy.y; y < xy.y + hh; y+=2) {
		hlines.add({x1, y}, {x2, y});
	}
}

void Striped_rectangle::draw_specifics(Painter& painter) const
{
	//draw the lines first so that the rectangle is drawn on top
	painter.set_color(hlines.color());
	painter.set_line_style(hlines.style());
	hlines.draw_specifics(painter);

	painter.set_color(this->color());
	painter.set_line_style(this->style());
	Rectangle::draw_specifics(painter);
}

void Striped_rectangle::move(int dx, int dy)
{
	Rectangle::move(dx, dy);
	hlines.move(dx, dy);
}
