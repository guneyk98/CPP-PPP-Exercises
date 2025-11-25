#include "PPP/GUI.h"
#include "PPP/Simple_window.h"

struct My_window : Simple_window {
	My_window(Point xy, int w, int h, const string& title);
private:
	Button quit_button;
};

int main()
{
	Application app;
	My_window win{{100, 100}, 1280, 720, "Ch14 01"};
	app.gui_main();
}

My_window::My_window(Point xy, int w, int h, const string& title)
	: Simple_window{xy, w, h, title},
	quit_button(Point{w-150,0}, 70, 20, "Quit", [this] { close(); })
{
	attach(quit_button);
}
