#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Application app;
	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex01");
	
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);


	constexpr Point r_pos{50, 50};
	constexpr int r_w = 100, r_h = 50;
	
	Rectangle r{r_pos, r_w, r_h};
	r.set_color(Color::blue);
	win.attach(r);

	constexpr int y_offset = 200;
	constexpr Point p_pos{r_pos.x, r_pos.y + y_offset};

	Polygon p;
	p.add(p_pos);
	p.add(Point{p_pos.x + r_w, p_pos.y});
	p.add(Point{p_pos.x + r_w, p_pos.y + r_h});
	p.add(Point{p_pos.x, p_pos.y + r_h});
	p.set_color(Color::red);
	win.attach(p);
	
	win.wait_for_button();
}
