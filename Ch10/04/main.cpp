#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;
	constexpr int win_x = 900, win_y = 500;
	constexpr int win_w = 600, win_h = 400;

	Application app;
	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex04");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point p{50, 50};
	constexpr int w = 100;
	Rectangle r{Point{0, 0}, w, w};
	std::array<Rectangle, 9> squares{ //no copy or move constructor...
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w},
		Rectangle{Point{0, 0}, w, w}
	};

	for (int i = 0; i < 9; ++i) {
		squares[i].move(p.x+(i%3)*w, p.y+(i/3)*w);
		squares[i].set_fill_color(i%2 ? Color::red : Color::white);
		win.attach(squares[i]);
	}

	win.wait_for_button();
}
