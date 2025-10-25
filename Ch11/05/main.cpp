#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 720, 720, "Ch11 Ex05");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr int num_cells_x = 16;
	constexpr int num_cells_y = 16;
	const int cell_w = win.x_max()/num_cells_x;
	const int cell_h = win.y_max()/num_cells_y;

	constexpr std::array<std::array<int, 3>, 16> colour_arr{{
		{{255,   0,   0}}, //red
		{{255,  85,   0}},
		{{255, 170,   0}},
		{{255, 255,   0}},
		{{170, 255,   0}},
		{{ 85, 255,   0}},
		{{  0, 255,   0}}, //green
		{{  0, 255,  85}},
		{{  0, 255, 170}},
		{{  0, 255, 255}},
		{{  0, 170, 255}},
		{{  0,  85, 255}},
		{{  0,   0, 255}}, //blue
		{{ 85,   0, 255}},
		{{170,   0, 255}},
		{{255,   0, 255}},
	}};

	Vector_ref<Rectangle> rects;
	for (int j = 0; j < num_cells_y; ++j) {
		const size_t c_idx = j % colour_arr.size();
		const int r = colour_arr[c_idx][0];
		const int g = colour_arr[c_idx][1];
		const int b = colour_arr[c_idx][2];

		for (int i = 0; i < num_cells_x; ++i) {
			const double t = static_cast<double>(i)/(num_cells_x-1);
			const double curved = std::pow(t, 1.5); //concentrate colours at lower values

			rects.push_back(make_unique<Rectangle>(Point{i*cell_w, j*cell_h}, cell_w, cell_h));
			rects[rects.size()-1].set_fill_color(Color(
				static_cast<int>(r*curved),
				static_cast<int>(g*curved),
				static_cast<int>(b*curved)
			));
			rects[rects.size()-1].set_color(Color::invisible);
			win.attach(rects[rects.size()-1]);
		}
	}
	win.wait_for_button();
}
