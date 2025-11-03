#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex02");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point centre{win.x_max()/2, win.y_max()/2};
	Circle c1{centre, 250};

	Circle c3{c1};	//error, copy constructor deleted
	Circle c2 = c1; //error, copy assigment operator deleted

	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.wait_for_button();
}
