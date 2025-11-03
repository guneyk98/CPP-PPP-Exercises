#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Immovable_circle : Circle {
	using Circle::Circle;
	virtual void move([[maybe_unused]] int dx, [[maybe_unused]] int dy) override {
		//do nothing or throw an exception
	}
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex04");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Immovable_circle c{{100, 100}, 100};
	win.attach(c);
	win.wait_for_button();
	c.move(100, 100); //does nothing
	win.wait_for_button();
}
