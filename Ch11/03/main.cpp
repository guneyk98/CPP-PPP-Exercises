#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>
using namespace Graph_lib;
constexpr double pi = numbers::pi_v<double>;

Point n(const Circle& c);
Point s(const Circle& c);
Point e(const Circle& c);
Point w(const Circle& c);
Point centre(const Circle& c);
Point ne(const Circle& c);
Point se(const Circle& c);
Point sw(const Circle& c);
Point nw(const Circle& c);

Point n(const Ellipse& e);
Point s(const Ellipse& e);
Point e(const Ellipse& e);
Point w(const Ellipse& e);
Point centre(const Ellipse& e);
Point ne(const Ellipse& e);
Point se(const Ellipse& e);
Point sw(const Ellipse& e);
Point nw(const Ellipse& e);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch11 Ex02");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Circle c{{400, 400}, 300};
	c.set_color(Color::green);

	Mark mc_n{n(c), 'n'};
	Mark mc_s{s(c), 's'};
	Mark mc_e{e(c), 'e'};
	Mark mc_w{w(c), 'w'};
	Mark mc_c{centre(c), 'c'};
	Text mc_ne{ne(c), "ne"};
	Text mc_se{se(c), "se"};
	Text mc_sw{sw(c), "sw"};
	Text mc_nw{nw(c), "nw"};

	win.attach(c);
	win.attach(mc_n);
	win.attach(mc_s);
	win.attach(mc_e);
	win.attach(mc_w);
	win.attach(mc_c);
	win.attach(mc_ne);
	win.attach(mc_se);
	win.attach(mc_sw);
	win.attach(mc_nw);
	win.wait_for_button();

	win.detach(c);
	win.detach(mc_n);
	win.detach(mc_s);
	win.detach(mc_e);
	win.detach(mc_w);
	win.detach(mc_c);
	win.detach(mc_ne);
	win.detach(mc_se);
	win.detach(mc_sw);
	win.detach(mc_nw);
	
	Ellipse el{{400, 400}, 300, 100};
	el .set_color(Color::green);

	Mark me_n{n(el), 'n'};
	Mark me_s{s(el), 's'};
	Mark me_e{e(el), 'e'};
	Mark me_w{w(el), 'w'};
	Mark me_c{centre(el), 'c'};
	Text me_ne{ne(el), "ne"};
	Text me_se{se(el), "se"};
	Text me_sw{sw(el), "sw"};
	Text me_nw{nw(el), "nw"};

	win.attach(el);
	win.attach(me_n);
	win.attach(me_s);
	win.attach(me_e);
	win.attach(me_w);
	win.attach(me_c);
	win.attach(me_ne);
	win.attach(me_se);
	win.attach(me_sw);
	win.attach(me_nw);
	win.wait_for_button();
}

Point n(const Circle& c)
{
	return {c.point(0).x + c.radius(), c.point(0).y};
}

Point s(const Circle& c)
{
	return {c.point(0).x + c.radius(), c.point(0).y + 2*c.radius()};
}

Point e(const Circle& c)
{
	return {c.point(0).x + 2*c.radius(), c.point(0).y + c.radius()};
}

Point w(const Circle& c)
{
	return {c.point(0).x, c.point(0).y + c.radius()};
}

Point centre(const Circle& c)
{
	return c.center();
}

Point ne(const Circle& c)
{
	const double r = static_cast<double>(c.radius());
	const int x = std::lround(std::sqrt((r*r)/2.0));
	const Point centre = c.center();
	return {centre.x + x, centre.y - x};
}

Point se(const Circle& c)
{
	const double r = static_cast<double>(c.radius());
	const int x = std::lround(std::sqrt((r*r)/2.0));
	const Point centre = c.center();
	return {centre.x + x, centre.y + x};
}

Point sw(const Circle& c)
{
	const double r = static_cast<double>(c.radius());
	const int x = std::lround(std::sqrt((r*r)/2.0));
	const Point centre = c.center();
	return {centre.x - x, centre.y + x};
}

Point nw(const Circle& c)
{
	const double r = static_cast<double>(c.radius());
	const int x = std::lround(std::sqrt((r*r)/2.0));
	const Point centre = c.center();
	return {centre.x - x, centre.y - x};
}

Point n(const Ellipse& e)
{
	return {e.point(0).x + e.major(), e.point(0).y};
}

Point s(const Ellipse& e)
{
	return {e.point(0).x + e.major(), e.point(0).y + 2*e.minor()};
}

Point e(const Ellipse& e)
{
	return {e.point(0).x + 2*e.major(), e.point(0).y + e.minor()};
}

Point w(const Ellipse& e)
{
	return {e.point(0).x, e.point(0).y + e.minor()};
}

Point centre(const Ellipse& e)
{
	return e.center();
}

Point ne(const Ellipse& e)
{
	const int x = std::lround(static_cast<double>(e.major())/std::sqrt(2.0));
	const int y = std::lround(static_cast<double>(e.minor())/std::sqrt(2.0));
	const Point centre = e.center();
	return {centre.x + x, centre.y - y};
}

Point se(const Ellipse& e)
{
	const int x = std::lround(static_cast<double>(e.major())/std::sqrt(2.0));
	const int y = std::lround(static_cast<double>(e.minor())/std::sqrt(2.0));
	const Point centre = e.center();
	return {centre.x + x, centre.y + y};
}

Point sw(const Ellipse& e)
{
	const int x = std::lround(static_cast<double>(e.major())/std::sqrt(2.0));
	const int y = std::lround(static_cast<double>(e.minor())/std::sqrt(2.0));
	const Point centre = e.center();
	return {centre.x - x, centre.y + y};
}

Point nw(const Ellipse& e)
{
	const int x = std::lround(static_cast<double>(e.major())/std::sqrt(2.0));
	const int y = std::lround(static_cast<double>(e.minor())/std::sqrt(2.0));
	const Point centre = e.center();
	return {centre.x - x, centre.y - y};
}
