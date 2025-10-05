#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Application app;
	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex03");
	
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Text t1{Point{50, 50}, "G"};
	Text t2{Point{150, 50}, "K"};

	t1.set_font_size(150);
	t2.set_font_size(150);

	t1.set_color(Color::dark_red);
	t2.set_color(Color::dark_green);

	win.attach(t1);
	win.attach(t2);

	win.wait_for_button();
}
