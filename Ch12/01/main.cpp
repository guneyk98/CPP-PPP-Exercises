#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

struct Smiley : Circle {
	Smiley(Point p, int rr)
		: Circle{p, rr},
		l_eye{{p.x - rr/3, p.y - rr/4}, rr/8},
		r_eye{{p.x + rr/3, p.y - rr/4}, rr/8},
		mouth{p, rr/2, rr/2, 225, 90} {
	}
	void draw_specifics(Painter& painter) const override;
private:
	Circle l_eye;
	Circle r_eye;
	Arc mouth;
};

struct Frowny : Circle {
	Frowny(Point p, int rr)
		: Circle{p, rr},
		l_eye{{p.x - rr/3, p.y - rr/4}, rr/8},
		r_eye{{p.x + rr/3, p.y - rr/4}, rr/8},
		mouth{{p.x, p.y + (3*rr)/4}, rr/2, rr/2, 45, 90} {
	}
	void draw_specifics(Painter& painter) const override;
private:
	Circle l_eye;
	Circle r_eye;
	Arc mouth;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex01");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	Point centre{win.x_max()/2, win.y_max()/2};

	Smiley smiley{centre, 250};
	win.attach(smiley);
	win.wait_for_button();

	win.detach(smiley);
	Frowny frowny{centre, 250};
	win.attach(frowny);
	win.wait_for_button();
}

void Smiley::draw_specifics(Painter& painter) const
{
	Circle::draw_specifics(painter);
	l_eye.draw_specifics(painter);
	r_eye.draw_specifics(painter);
	mouth.draw_specifics(painter);
}

void Frowny::draw_specifics(Painter& painter) const
{
	Circle::draw_specifics(painter);
	l_eye.draw_specifics(painter);
	r_eye.draw_specifics(painter);
	mouth.draw_specifics(painter);
}
