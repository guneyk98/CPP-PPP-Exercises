#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	Application app;

	//Trying to draw a shape that doesn't fit inside the window
	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Simple_window win1(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex06");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win1.attach(background_fill);

	//only the sections inside the window are drawn
	Rectangle r1{Point{win1.x_max()-50, win1.y_max()-50}, 1000, 1000};
	r1.set_fill_color(Color::red);
	win1.attach(r1);
	win1.wait_for_button();
	win1.close();



	//Creating a window that doesn't fit inside my screen
	constexpr int win2_x = 900, win2_y = 500;
	constexpr int win2_w = 2*2560, win2_h = 2*1440; //twice my screen res

	Simple_window win2(Point{win2_x, win2_y}, win2_w, win2_h, "Ch10 Ex06");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill2{Point{0, 0}, win2_w, win2_h};
	background_fill2.set_fill_color(Color::white);
	win2.attach(background_fill2);

	Rectangle r2{Point{win2.x_max()-50, win2.y_max()-50}, 1000, 1000};
	r2.set_fill_color(Color::red);
	win2.attach(r2);
	std::cout << win2.x_max() << '\t' << win2.y_max() << '\n';
	win2.wait_for_button();
	
	//The operating system reduces the size of the window to a maximum; however,
	//the size of the window in memory is not reduced


}
