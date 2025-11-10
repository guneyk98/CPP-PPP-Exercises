#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <numbers>

constexpr double pi = numbers::pi_v<double>;

struct Binary_tree : Shape {
	Binary_tree(Point p, int r, int num_levels);
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	virtual void draw_nodes(Painter& painter) const;
protected:
	int num_levels;
	int r;
	Lines lines;
	std::vector<Point> nodes;
};

struct Regular_polygon : Shape {
	Regular_polygon(Point centre, int num_sides, double r, double rot);
	void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	Point centre() const { return c; }
private:
	Point c;
};

struct Binary_tree_tri : Binary_tree {
	using Binary_tree::Binary_tree;
	virtual void draw_nodes(Painter& painter) const override;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex14");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);


	Binary_tree_tri btt{{win.x_max()/2, 100}, 25, 4};
	win.attach(btt);
	win.wait_for_button();
	btt.move(100, 50);
	win.wait_for_button();
}

Binary_tree::Binary_tree(Point p, int r, int num_levels)
	: r{r}, num_levels{num_levels}
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

			lines.add(
				{x + dx, y + dy},
				{parent_c.x - dx, parent_c.y - dy}
			);
		}
	}
}

void Binary_tree::draw_specifics(Painter& painter) const
{
	lines.draw_specifics(painter);
	draw_nodes(painter);
}

void Binary_tree::move(int dx, int dy)
{
	lines.move(dx, dy);
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].x += dx;
		nodes[i].y += dy;
	}
	redraw();
}

void Binary_tree::draw_nodes(Painter& painter) const
{
	for (int i = 0; i < nodes.size(); ++i)
		painter.draw_ellipse(nodes[i], r, r);
}

Regular_polygon::Regular_polygon(Point centre, int num_sides, double r, double rot)
	: c{centre}
{
	const double theta = (2.0*pi)/num_sides;
	for (int i = 0; i < num_sides; ++i) {
		const int x = centre.x + std::lround(r*std::cos(i*theta + rot));
		const int y = centre.y - std::lround(r*std::sin(i*theta + rot));
		add({x,	y});
	}
}

void Regular_polygon::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}

void Regular_polygon::move(int dx, int dy)
{
	Shape::move(dx, dy);
	c.x += dx;
	c.y += dy;
}

void Binary_tree_tri::draw_nodes(Painter& painter) const
{
	for (int i = 0; i < nodes.size(); ++i) {
		painter.draw_polygon(Regular_polygon{
			nodes[i],
			3,
			static_cast<double>(r),
			pi/2.0
			}
		);
	}
}
