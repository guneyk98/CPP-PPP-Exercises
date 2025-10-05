#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	Application app;

	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Simple_window win(Point{win_x, win_y}, win_w, win_h, "orangutan");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	const int img_w = win_w/2;
	const int img_h = win_h/2;
	Image img{Point{0, 0}, "img.png"};
	img.scale(img_w, img_h, false);
	win.attach(img);

	Text caption{Point{img.point(0).x + img_w/4, img.point(0).y+img_h}, "orangutan"};
	win.attach(caption);

	win.wait_for_button();
}
