#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Bar_graph : Shape {
	Bar_graph(Point orig, int w, int h, const std::vector<double>& data);

	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
private:
	int width, height;
	Axis xa, ya;
	Vector_ref<Rectangle> rects;
};

int main()
{
	Application app;
	Simple_window win({0, 0}, 1200, 1200, "Ch13 Ex06");
	//fill background white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	const std::vector<double> data{
		2.41,
		9.53,
		0.34,
		5.23,
		3.21
	};

	Bar_graph bg{{200, 1000}, 800, 800, data};
	win.attach(bg);
	win.wait_for_button();
}

Bar_graph::Bar_graph(Point orig, int w, int h, const std::vector<double>& data)
	: xa{Axis::x, orig, w}, ya{Axis::y, orig, h}, width{w}, height{h}
{
	double max = data[0];
	for (int i = 1; i < data.size(); ++i) {
		if (data[i] < 0.0)
			error("bar chart only accepts non-negative numbers");
		if (data[i] > max)
			max = data[i];
	}

	constexpr double ratio = 0.5; //barw/gap
	const double size = static_cast<double>(data.size());
	const double barw = w/(size + (size+1.0)*ratio);
	const double gap = barw*ratio;

	for (int i = 0; i < data.size(); ++i) {
		const int x = orig.x + std::lround(i*barw + (i+1)*gap);
		const double barh = h*(data[i]/max);
		const int y = orig.y - std::lround(barh);
		rects.push_back(std::make_unique<Rectangle>(
			Point{x, y},
			std::lround(barw),
			std::lround(barh)
		));
	}
}

void Bar_graph::draw_specifics(Painter& painter) const
{
	xa.draw_specifics(painter);
	ya.draw_specifics(painter);
	for (int i = 0; i < rects.size(); ++i)
		rects[i].draw_specifics(painter);
}

void Bar_graph::move(int dx, int dy)
{
	xa.move(dx, dy);
	ya.move(dx, dy);
	for (int i = 0; i < rects.size(); ++i)
		rects[i].move(dx, dy);
	redraw();
}
