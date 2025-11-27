#include "PPP/GUI.h"
#include "PPP/Window.h"
#include "PPP/std_lib_facilities.h"

using namespace Graph_lib;


int main()
{
	Application app;
	Window win{{100, 100}, 1280, 720, "Ch14 03"};

	const Point p{50, 50};
	constexpr int size = 100;

	Image img{p, "img.png"};

	Button button{p, size, size, "", [&]() {
		const int x = randint(0, win.x_max()-size);
		const int y = randint(0, win.y_max()-size);

		img.move(x-img.point(0).x, y-img.point(0).y);
		button.move(x-button.loc.x, y-button.loc.y);
	}};

	win.attach(button);
	win.attach(img);
	app.gui_main();
}
