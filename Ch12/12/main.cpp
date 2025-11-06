#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Box : Shape {
	Box(Point p, int w, int h, int corner_r);
	void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	Vector_ref<Arc> arcs;
	Vector_ref<Pie> corners;
};

struct Pseudo_window : Box {
	Pseudo_window(Point p, int ww, int hh, std::string s = "", int corner_r = 10) :
		Box{p, ww, hh, corner_r},
		label{{p.x + corner_r*2, p.y+8}, s},
		top_bar{{p.x, p.y+30}, {p.x+ww, p.y+30}},
		button_marks{"-OX", {{p.x+ww-80, p.y+17}, {p.x+ww-50, p.y+14}, {p.x+ww-20, p.y+14}}} {
	}
	void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	Text label;
	Line top_bar;
	Marks button_marks;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex12");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Pseudo_window pw{{100, 100}, 400, 400, "Window"};
	pw.set_fill_color(Color::red);
	win.attach(pw);
	win.wait_for_button();
	pw.move(50, 100);
	win.wait_for_button();
}

Box::Box(Point p, int w, int h, int corner_r)
{
	const int r = corner_r;

	//centre points for arcs and corners
	const std::array<Point, 4> arc_pos{
		Point{p.x + r,	 p.y + r},		//top left
		Point{p.x + w-r, p.y + r},		//top right
		Point{p.x + w-r, p.y + h-r},	//bottom right
		Point{p.x + r,	 p.y + h-r}		//bottom left
	};
	constexpr std::array<int, 4> arc_angle{90, 0, 270, 180};

	for (int i = 0; i < 4; ++i) {
		arcs.push_back(make_unique<Arc>(arc_pos[i], r, r, arc_angle[i], 90));
		corners.push_back(make_unique<Pie>(arc_pos[i], r, r, arc_angle[i], 90));
	}

	//these points make a plus shaped polygon
	add({p.x + r, p.y + r});
	add({p.x + r, p.y});
	add({p.x + w-r, p.y});
	add({p.x + w-r, p.y + r});
	add({p.x + w, p.y + r});
	add({p.x + w, p.y + h-r});
	add({p.x + w-r, p.y + h-r});
	add({p.x + w-r, p.y + h});
	add({p.x + r, p.y + h});
	add({p.x + r, p.y + h-r});
	add({p.x, p.y + h-r});
	add({p.x, p.y + r});
}

void Box::draw_specifics(Painter& painter) const
{
	//draw filled shape without borders
	painter.set_line_style(style());
	painter.set_color(Color::invisible);
	painter.draw_polygon(*this);
	for (int i = 0; i < corners.size(); ++i)
		corners[i].draw_specifics(painter);

	//draw border
	painter.set_line_style(style());
	painter.set_color(color());
	for (int i = 2; i < number_of_points(); i += 3)
		painter.draw_line(point(i-1), point(i));
	for (int i = 0; i < corners.size(); ++i)
		arcs[i].draw_specifics(painter);
}

void Box::move(int dx, int dy)
{
	Shape::move(dx, dy);
	for (int i = 0; i < arcs.size(); ++i) {
		arcs[i].move(dx, dy);
		corners[i].move(dx, dy);
	}
	redraw();
}

void Pseudo_window::draw_specifics(Painter& painter) const
{
	Box::draw_specifics(painter);
	label.draw_specifics(painter);
	top_bar.draw_specifics(painter);
	button_marks.draw_specifics(painter);
}

void Pseudo_window::move(int dx, int dy)
{
	Box::move(dx, dy);
	label.move(dx, dy);
	top_bar.move(dx, dy);
	button_marks.move(dx, dy);
	redraw();
}
