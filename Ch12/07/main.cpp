#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Striped_closed_polyline : Closed_polyline {
	Striped_closed_polyline(std::initializer_list<Point> p = {}) : Closed_polyline(p) {
		construct_lines();
	}
	void set_fill_color(Color col) { hlines->set_color(col); redraw(); }
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	void add(Point p);
private:
	void construct_lines();
	std::unique_ptr<Lines> hlines;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex07");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point centre{win.x_max()/2, win.y_max()/2};
	Striped_closed_polyline poly;

	poly.add({250, 50});
	poly.add({550, 750});
	poly.add({750, 550});
	poly.add({120, 700});
	poly.add({150, 500});
	poly.add({200, 550});
	poly.add({600, 75});
	poly.add({50, 250});

	win.attach(poly);
	win.wait_for_button();

	poly.set_fill_color(Color::red);
	win.wait_for_button();

	poly.set_color(Color::invisible);
	win.wait_for_button();

}

void Striped_closed_polyline::draw_specifics(Painter& painter) const
{
	//draw the lines first so that the borders of the polyline are drawn on top
	painter.set_line_style(hlines->style());
	painter.set_color(hlines->color());
	hlines->draw_specifics(painter);

	painter.set_line_style(this->style());
	painter.set_color(this->color());
	Closed_polyline::draw_specifics(painter);
}

void Striped_closed_polyline::move(int dx, int dy)
{
	Closed_polyline::move(dx, dy);
	hlines->move(dx, dy);
}

void Striped_closed_polyline::construct_lines()
{
	const int num_points = number_of_points();
	if (num_points < 3)
		return;

	//inefficient but necessary because Shape does not allow the removal of points...
	hlines.reset(new Lines);
	hlines->set_color(Color::invisible);

	//find y_min and y_max to reduce loop interations
	int y_min = point(0).y;
	int y_max = y_min;
	for (int i = 1; i < num_points; ++i) {
		if (point(i).y < y_min)
			y_min = point(i).y;
		if (point(i).y > y_max)
			y_max = point(i).y;
	}

	for (int y = y_min; y < y_max; y += 2) {
		std::vector<int> x_intersects;
		//find all intersects at y
		for (int i = 0; i < num_points; ++i) {
			const int y1 = point(i).y;
			const int y2 = point((i+1)%num_points).y;

			if (y1 == y2 || (y1 < y && y2 < y) || (y1 > y && y2 > y))
				continue;
			
			const int x1 = point(i).x;
			const int x2 = point((i+1)%num_points).x;
			const int x = std::lround(x1 + (x2-x1) * (y-y1)/static_cast<double>(y2-y1));
			x_intersects.push_back(x);
		}
		std::sort(x_intersects.begin(), x_intersects.end());
		for (int i = 1; i < x_intersects.size(); i += 2)
			hlines->add({x_intersects[i-1], y}, {x_intersects[i], y});
	}
}

void Striped_closed_polyline::add(Point p)
{
	Closed_polyline::add(p);
	construct_lines();
}
