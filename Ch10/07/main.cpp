#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	Application app;

	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex07");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	//house boundary
	const int hx_min = win.x_max()/10;
	const int hx_max = (9*win.x_max())/10;
	const int hy_min = win.y_max()/10;
	const int hy_max = (9*win.y_max())/10;

	Rectangle base{Point{hx_min, win.y_max()/2}, Point{hx_max, hy_max}};
	base.set_fill_color(Color::red);

	Closed_polyline roof;
	roof.add(base.point(0));
	roof.add(Point{base.point(0).x + base.width(), base.point(0).y});
	roof.add(Point{(roof.point(0).x+roof.point(1).x)/2, hy_min});
	roof.set_fill_color(Color::green);

	const int door_w = base.width()/6;
	const int door_h = (2*base.height())/3;
	const int door_x = base.point(0).x + base.width()/2 - door_w/2;
	const int door_y = base.point(0).y + base.height() - door_h;
	Rectangle door{Point{door_x, door_y}, door_w, door_h};
	door.set_fill_color(Color::black);

	const int hwin_w = door_w;
	const int hwin_h = hwin_w;
	const int hwin1_x = (base.point(0).x+door.point(0).x)/2 - hwin_w/2;
	const int hwin1_y = base.point(0).y + base.height()/2 - hwin_h/2;
	const int hwin2_x = (base.point(0).x+base.width()+door.point(0).x+door_w)/2 - hwin_w/2;
	const int hwin2_y = hwin1_y;

	Rectangle hwin1{Point{hwin1_x, hwin1_y}, hwin_w, hwin_h};
	Rectangle hwin2{Point{hwin2_x, hwin2_y}, hwin_w, hwin_h};
	hwin1.set_fill_color(Color::cyan);
	hwin2.set_fill_color(Color::cyan);

	Line bar1h{
		Point{hwin1.point(0).x, hwin1.point(0).y+hwin1.height()/2},
		Point{hwin1.point(0).x+hwin1.width(), hwin1.point(0).y+hwin1.width()/2}
	};
	Line bar2h{
		Point{hwin2.point(0).x, hwin2.point(0).y+hwin2.height()/2},
		Point{hwin2.point(0).x+hwin2.width(), hwin2.point(0).y+hwin2.height()/2}
	};
	Line bar1v{
		Point{hwin1.point(0).x+hwin1.width()/2, hwin1.point(0).y},
		Point{hwin1.point(0).x+hwin1.width()/2, hwin1.point(0).y+hwin1.height()}
	};
	Line bar2v{
		Point{hwin2.point(0).x+hwin2.width()/2, hwin2.point(0).y},
		Point{hwin2.point(0).x+hwin2.width()/2, hwin2.point(0).y+hwin2.height()}
	};

	const int chim_w = base.width()/8;
	const int chim_h = roof.point(0).y-roof.point(2).y;
	const int chim_x = (roof.point(0).x+roof.point(2).x)/2 - chim_w/2;
	const int chim_y = roof.point(2).y;
	Rectangle chimney{Point{chim_x, chim_y}, chim_w, chim_h};
	chimney.set_fill_color(Color::black);

	win.attach(base);
	win.attach(chimney);
	win.attach(roof);
	win.attach(door);
	win.attach(hwin1);
	win.attach(hwin2);
	win.attach(bar1h);
	win.attach(bar2h);
	win.attach(bar1v);
	win.attach(bar2v);
	win.wait_for_button();

}
