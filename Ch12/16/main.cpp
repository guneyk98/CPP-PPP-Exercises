#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <numbers>

constexpr double pi = numbers::pi_v<double>;

struct Arrow : Shape {
	Arrow(Point p1, Point p2, double len = 10.0, double theta = pi/6.0);
	void draw_specifics(Painter& painter) const override;
};

struct Binary_tree : Shape {
	Binary_tree(Point p, int r, int num_levels, Color arrow_col, bool arrow_down = true);
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	virtual void draw_nodes(Painter& painter) const;
	void add_text(const std::string& path, const std::string& s);
protected:
	int num_levels;
	int r;
	Vector_ref<Arrow> lines;
	Vector_ref<Text> text;
	std::vector<Point> nodes;
	Color a_col;
};

int path_to_idx(const std::string& path);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex16");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Binary_tree bt{{win.x_max()/2, 100}, 25, 4, Color::red};
	bt.add_text("lrr", "text");

	win.attach(bt);
	win.wait_for_button();
	bt.move(100, 50);
	win.wait_for_button();
}

Arrow::Arrow(Point p1, Point p2, double len, double theta)
{
	add(p1);
	add(p2);

	double x21 = p1.x - p2.x;
	double y21 = p1.y - p2.y;
	const double mag = std::sqrt(x21*x21 + y21*y21);
	x21 /= mag; //normalise
	y21 /= mag;

	const double costheta = std::cos(theta);
	const double sintheta = std::sin(theta);

	//2D rotation matrix
	const int x23 = std::lround(len*(x21*costheta - y21*sintheta));
	const int y23 = std::lround(len*(x21*sintheta + y21*costheta));
	const int x24 = std::lround(len*(x21*costheta + y21*sintheta));
	const int y24 = std::lround(len*(-x21*sintheta + y21*costheta));

	add({p2.x+x23, p2.y+y23});
	add({p2.x+x24, p2.y+y24});
}

void Arrow::draw_specifics(Painter& painter) const
{
	painter.draw_line(point(0), point(1));
	painter.draw_line(point(1), point(2));
	painter.draw_line(point(1), point(3));
}

Binary_tree::Binary_tree(Point p, int r, int num_levels, Color arrow_col, bool arrow_down)
	: r{r}, num_levels{num_levels}, a_col{arrow_col}
{
	//centre-to-centre distance between nodes
	const int x_dis = 3*r;
	const int y_dis = 3*r;

	for (int j = 0; j < num_levels; ++j) {
		const int num_nodes = 1 << j;
		const int y = p.y + y_dis*j;
		const int level_spacing = x_dis*(1 << (num_levels-1-j));
		const int x_min_level = p.x - std::lround(((num_nodes-1)*level_spacing)/2.0);

		for (int i = 0; i < num_nodes; ++i) {
			const int x = x_min_level + i*level_spacing;
			nodes.push_back(Point{x, y});

			if (j == 0)
				continue;

			Point parent_c = nodes[(nodes.size()-2)/2];
			int dx = parent_c.x - x;
			int dy = parent_c.y - y;
			const double mag = std::sqrt(dx*dx + dy*dy);
			dx = std::lround((r*dx)/mag);
			dy = std::lround((r*dy)/mag);

			const Point& p1{parent_c.x - dx, parent_c.y - dy};
			const Point& p2{x + dx, y + dy};

			if (arrow_down)
				lines.push_back(make_unique<Arrow>(p1, p2));
			else
				lines.push_back(make_unique<Arrow>(p2, p1));
		}
	}
}

void Binary_tree::draw_specifics(Painter& painter) const
{
	draw_nodes(painter);
	painter.set_color(a_col);
	for (int i = 0; i < lines.size(); ++i)
		lines[i].draw_specifics(painter);

	painter.set_color(color());
	for (int i = 0; i < text.size(); ++i)
		text[i].draw_specifics(painter);
}

void Binary_tree::move(int dx, int dy)
{
	for (int i = 0; i < lines.size(); ++i)
		lines[i].move(dx, dy);
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].x += dx;
		nodes[i].y += dy;
	}
	for (int i = 0; i < text.size(); ++i)
		text[i].move(dx, dy);
	redraw();
}

void Binary_tree::draw_nodes(Painter& painter) const
{
	for (int i = 0; i < nodes.size(); ++i)
		painter.draw_ellipse(nodes[i], r, r);
}

void Binary_tree::add_text(const std::string& path, const std::string& s)
{
	int idx = path_to_idx(path);
	if (idx >= nodes.size())
		error("path represents node that does not exist");
	
	const Point c = nodes[idx];
	text.push_back(make_unique<Text>(Point{c.x-r, c.y}, s));
}

int path_to_idx(const std::string& path)
{
	int idx = 0;
	for (char ch : path) {
		switch (ch) {
		case 'l': case 'L':
			idx = 2*idx + 1; break;
		case 'r': case 'R':
			idx = 2*idx + 2; break;
		default:
			error("invalid path format");
		}
	}
	return idx;
}
