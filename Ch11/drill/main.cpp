#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main()
{
	using namespace Graph_lib;

	Application app;
	Simple_window win(Point{50, 50}, 800, 1000, "My window");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr int grid_size = 800;
	constexpr int cell_size = 100;

	Lines grid;
	for (int x = cell_size; x < grid_size; x += cell_size)
		grid.add(Point{x, 0}, Point{x, grid_size});
	for (int y = cell_size; y < grid_size; y += cell_size)
		grid.add(Point{0, y}, Point{grid_size, y});

	win.attach(grid);
	win.wait_for_button();

	Vector_ref<Rectangle> squares;
	for (int x = 0; x < grid_size; x += cell_size) {
		squares.push_back(std::make_unique<Rectangle>(Point{x, x}, cell_size, cell_size));
		squares[squares.size()-1].set_fill_color(Color::red);
		win.attach(squares[squares.size()-1]);
	}
	win.wait_for_button();

	const std::string img_path = "img.png";
	std::array<Image, 3> images{
		Image{{200, 0}, img_path},
		Image{{500, 400}, img_path},
		Image{{0, 500}, img_path}
	};
	for (int i = 0; i < images.size(); ++i)
		win.attach(images[i]);
	win.wait_for_button();

	Image img{Point{0, 0}, "img2.png"};
	win.attach(img);
	for (;;) {
		win.wait_for_button();
		const int& x = img.point(0).x;
		const int& y = img.point(0).y;
		constexpr int max = grid_size - cell_size;

		if (x == max) {
			if (y == max)
				img.move(-max, -max);
			else
				img.move(-max, cell_size);
		} else {
			img.move(cell_size, 0);
		}
	}
}
