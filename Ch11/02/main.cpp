#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

Point n(const Rectangle& r);
Point s(const Rectangle& r);
Point e(const Rectangle& r);
Point w(const Rectangle& r);
Point centre(const Rectangle& r);
Point ne(const Rectangle& r);
Point se(const Rectangle& r);
Point sw(const Rectangle& r);
Point nw(const Rectangle& r);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch11 Ex02");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Rectangle r{{100, 100}, {700, 700}};
	r.set_color(Color::green);

	Mark m_n{n(r), 'n'};
	Mark m_s{s(r), 's'};
	Mark m_e{e(r), 'e'};
	Mark m_w{w(r), 'w'};
	Mark m_c{centre(r), 'c'};
	Text m_ne{ne(r), "ne"};
	Text m_se{se(r), "se"};
	Text m_sw{sw(r), "sw"};
	Text m_nw{nw(r), "nw"};

	win.attach(r);
	win.attach(m_n);
	win.attach(m_s);
	win.attach(m_e);
	win.attach(m_w);
	win.attach(m_c);
	win.attach(m_ne);
	win.attach(m_se);
	win.attach(m_sw);
	win.attach(m_nw);
	win.wait_for_button();
}

Point n(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y};
}

Point s(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y + r.height()};
}

Point e(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y + r.height()/2};
}

Point w(const Rectangle& r)
{
	return {r.point(0).x, r.point(0).y + r.height()/2};
}

Point centre(const Rectangle& r)
{
	return {r.point(0).x + r.width()/2, r.point(0).y + r.height()/2};
}

Point ne(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y};
}

Point se(const Rectangle& r)
{
	return {r.point(0).x + r.width(), r.point(0).y + r.height()};
}

Point sw(const Rectangle& r)
{
	return {r.point(0).x, r.point(0).y + r.height()};
}

Point nw(const Rectangle& r)
{
	return r.point(0);
}
