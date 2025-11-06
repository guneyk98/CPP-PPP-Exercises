#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Binary_tree : Shape {
	Binary_tree(Point p, int r, int num_levels);
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	Lines lines;
	Vector_ref<Circle> nodes;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex13");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);


	Binary_tree bt{{win.x_max()/2, 100}, 25, 4};
	win.attach(bt);
	win.wait_for_button();
	bt.move(100, 50);
	win.wait_for_button();
}

Binary_tree::Binary_tree(Point p, int r, int num_levels)
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
			nodes.push_back(make_unique<Circle>(Point{x, y}, r));

			if (j == 0)
				continue;

			Point parent_c = nodes[(nodes.size()-2)/2].center();
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
	for (int i = 0; i < nodes.size(); ++i)
		nodes[i].draw_specifics(painter);
	lines.draw_specifics(painter);
}

void Binary_tree::move(int dx, int dy)
{
	lines.move(dx, dy);
	for (int i = 0; i < nodes.size(); ++i)
		nodes[i].move(dx, dy);
	redraw();
}
