#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Application app;
	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex05");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Rectangle r{Point{50, 50}, (2*win.x_max())/3, (3*win.y_max())/4};
	r.set_style(Line_style(Line_style::solid, 10));
	r.set_color(Color::red);
	win.attach(r);

	win.wait_for_button();
}
