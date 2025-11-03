#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <numbers>

using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

struct Regular_octagon : Shape {
	Regular_octagon(Point centre, double radius);
	virtual void draw_specifics(Painter& painter) const override;
};

bool print_test(bool result);
bool test_oct(Regular_octagon& oct);
bool test_move(Shape& shape);
bool test_set_color(Shape& shape);
bool test_set_fill_color(Shape& shape);
bool test_set_style(Shape& shape);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex08");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point centre{win.x_max()/2, win.y_max()/2};

	Regular_octagon oct{centre, 250};
	
	if (test_oct(oct))
		std::cout << "All tests passed.\n";
	else
		std::cout << "One or more tests failed.\n";

	win.attach(oct);
	win.wait_for_button();

}

Regular_octagon::Regular_octagon(Point centre, double radius)
{
	for (int i = 0; i < 8; ++i) {
		const int x = centre.x + std::lround(radius * std::cos(i*pi/3));
		const int y = centre.y + std::lround(radius * std::sin(i*pi/3));
		add({x,	y});
	}
}

void Regular_octagon::draw_specifics(Painter& painter) const
{
	painter.draw_polygon(*this);
}

bool print_test(bool result)
{
	if (result)
		std::cout << "PASS\n";
	else
		std::cout << "FAIL\n";
	return result;
}

bool test_oct(Regular_octagon& oct)
{
	int num_failed = 0;
	std::cout << "Test move(): ";
	if (!print_test(test_move(oct)))
		++num_failed;

	std::cout << "Test set_color(): ";
	if (!print_test(test_set_color(oct)))
		++num_failed;

	std::cout << "Test set_fill_color(): ";
	if (!print_test(test_set_fill_color(oct)))
		++num_failed;

	std::cout << "Test set_style(): ";
	if (!print_test(test_set_style(oct)))
		++num_failed;

	std::cout << "Number of tests failed: " << num_failed << '\n';
	return !num_failed;
}

bool test_move(Shape& shape)
{
	int num_points = shape.number_of_points();
	std::vector<Point> p;
	for (int i = 0; i < num_points; ++i)
		p.push_back(shape.point(i));

	const int dx = 100;
	const int dy = 50;
	shape.move(dx, dy);

	if (num_points != shape.number_of_points())
		return false;

	for (int i = 0; i < num_points; ++i)
		if (shape.point(i).x != p[i].x + dx && shape.point(i).y != p[i].y + dy)
			return false;

	return true;
}

bool test_set_color(Shape& shape)
{
	Color::Color_type ct = Color::red;
	shape.set_color(ct);
	Color c{ct};
	
	return shape.color().red_component() == c.red_component() &&
		shape.color().green_component() == c.green_component() &&
		shape.color().blue_component() == c.blue_component();
}

bool test_set_fill_color(Shape& shape)
{
	Color::Color_type ct = Color::blue;
	shape.set_fill_color(ct);
	Color c{ct};

	return shape.fill_color().red_component() == c.red_component() &&
		shape.fill_color().green_component() == c.green_component() &&
		shape.fill_color().blue_component() == c.blue_component();
}

bool test_set_style(Shape& shape)
{
	int width = 10;
	Line_style::Line_style_type lst = Line_style::dashdotdot;
	shape.set_style(Line_style{lst, width});

	return shape.style().width() == width &&
		shape.style().style() == lst;
}
