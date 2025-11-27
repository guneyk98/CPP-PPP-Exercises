#include "PPP/GUI.h"
#include "PPP/Simple_window.h"

struct My_window : Simple_window {
	My_window(Point xy, int w, int h, const string& title);
private:
	Button quit_button;
};

struct CB_window : My_window {
	CB_window(Point xy, int w, int h, const string& title);
private:
	Vector_ref<Button> buttons;
};

int main()
{
	Application app;
	CB_window win{{100, 100}, 1280, 720, "Ch14 02"};
	app.gui_main();
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Simple_window{xy, w, h, title},
	quit_button(Point{w-150,0}, 70, 20, "Quit", [this] { close(); })
{
	attach(quit_button);
}

CB_window::CB_window(Point xy, int w, int h, const string& title)
	: My_window{xy, w, h, title}
{
	constexpr int size = 2;
	constexpr int bsize = 100;

	for (int j = 0; j < size; ++j) {
		for (int i = 0; i < size; ++i) {
			const Point pos{i*bsize, j*bsize};
			buttons.push_back(std::make_unique<Button>(
				pos,
				bsize,
				bsize,
				std::string(1, static_cast<char>('a' + i + size * j)),
				[=]() { std::cout << "pos: " << pos.x << ", " << pos.y << '\n'; }
			));
			attach(buttons[buttons.size()-1]);
		}
	}
}
