#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex11");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Vector_ref<Rectangle> vr;
	
	const int max = 32;
	const int side = 18;
	const int left = 10;
	const int top = 100;
	int colour_index = 0;

	for (int i = 0; i < max; ++i) {
		for (int j = 0; j < 8; ++j) {
			vr.push_back(make_unique<Rectangle>(Point{i*side+left, j*side+top}, side, side));
			vr[vr.size()-1].set_fill_color(colour_index);
			vr[vr.size()-1].set_color(Color::invisible);
			++colour_index;
			win.attach(vr[vr.size()-1]);
		}
	}
	win.wait_for_button();
}
