#include "PPP/GUI.h"
#include "PPP/Window.h"

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Application& app, Point xy, int w, int h, const std::string& title);
	Open_polyline lines;

private:
	Application* app = nullptr;
	Button quit_button;
	In_box next_xy;
	Out_box xy_out;
	void next();
	void quit();
};

struct Color_window : Lines_window {
	Color_window(Application& app, Point xy, int w, int h, const std::string& title);
private:
	void change_color(Color c) { lines.set_color(c); }
	void hide_color_menu() { color_menu.hide(); color_menu_button.show(); }
	Button color_menu_button;
	Menu color_menu;
};

struct Style_window : Color_window {
	Style_window(Application& app, Point xy, int w, int h, const std::string& title);
private:
	void change_style(Line_style s) { lines.set_style(s); }
	void hide_style_menu() { style_menu.hide(); style_menu_button.show(); }
	Button style_menu_button;
	Menu style_menu;
};

int main()
{
	try {
		Application app;
		Style_window win{app, {100, 100}, 600, 400, "lines"};
		app.gui_main();
	} catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Some exception\n";
		return 2;
	}
}

Lines_window::Lines_window(Application& app, Point xy, int w, int h, const std::string& title)
	: Window(xy, w, h, title),
	app{&app},
	quit_button{{x_max()-70, 0}, 70, 20, "Quit", [this]() { quit(); }},
	next_xy{{250, 0}, 50, 20, "next xy:", [this]() { next(); }},
	xy_out{{10, 10}, "current (x,y): "}
{
	attach(lines);
	attach(quit_button);

	next_xy.hide_buttons();
	attach(next_xy);
	next_xy.show();

	xy_out.label.set_font_size(8);
	xy_out.data.set_font_size(8);
	attach(xy_out);
}

void Lines_window::next()
{
	if (next_xy.last_result() == In_box::accepted) {
		std::string s = next_xy.last_string_value();
		std::istringstream iss{s};
		int x = 0;
		char ch = 0;
		int y = 0;
		iss >> x >> ch >> y;
		lines.add({x, y});

		std::ostringstream oss;
		oss << '(' << x << ',' << y << ')';
		xy_out.put(oss.str());
	}
	next_xy.clear_last_result();
}

void Lines_window::quit()
{
	end_button_wait();
	next_xy.dismiss();
	app->quit();
}

Color_window::Color_window(Application& app, Point xy, int w, int h, const std::string& title)
	: Lines_window(app, xy, w, h, title),
	color_menu_button{{x_max()-80, 30}, 80, 20, "color menu",
		[&] { color_menu_button.hide(); color_menu.show(); }},
	color_menu{{x_max()-70, 40}, 70, 20, Menu::vertical, "color"}
{
	attach(color_menu);
	color_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "red",
		[&] { change_color(Color::red); hide_color_menu(); }));
	color_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "blue",
		[&] { change_color(Color::blue); hide_color_menu(); }));
	color_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "black",
		[&] { change_color(Color::black); hide_color_menu(); }));
	attach(color_menu_button);
	hide_color_menu();
}

Style_window::Style_window(Application& app, Point xy, int w, int h, const std::string& title)
	: Color_window(app, xy, w, h, title),
	style_menu_button{{x_max()-80, 130}, 80, 20, "style menu",
		[&] { style_menu_button.hide(); style_menu.show(); }},
	style_menu{{x_max()-70, 140}, 70, 20, Menu::vertical, "style"}
{
	attach(style_menu);
	style_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "solid",
		[&] { change_style(Line_style::solid); hide_style_menu(); }));
	style_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "dash",
		[&] { change_style(Line_style::dash); hide_style_menu(); }));
	style_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "dot",
		[&] { change_style(Line_style::dot); hide_style_menu(); }));
	style_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "dashdot",
		[&] { change_style(Line_style::dashdot); hide_style_menu(); }));
	style_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, "dashdotdot",
		[&] { change_style(Line_style::dashdotdot); hide_style_menu(); }));
	attach(style_menu_button);
	hide_style_menu();
}
