#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

template<typename T>
class Fnct : public Shape {
public:
	Fnct(std::function<double(double, T)> f, T prec, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	void reset_func(std::function<double(double)> new_f);
	void reset_prec(T new_prec);
	void reset_range(double new_r1, double new_r2);
	void reset_orig(Point new_orig);
	void reset_count(int new_count);
	void reset_scale(double new_xscale, double new_yscale);

private:
	std::function<double(double, T)> f;
	T prec;
	double r1, r2;
	Point orig;
	int count;
	double xscale, yscale;
	std::vector<Point> v; //can't delete elements from 'points'

	void calculate_points();
};

double fac(int n);
double term(double x, int n);
double exp_n(double x, int n);

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch13 Ex03");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	const Point c{win.x_max()/2, win.y_max()/2};

	Fnct<int> f{exp_n, 0, -10, 10, c};
	win.attach(f);
	win.wait_for_button();

	for (int i = 1; i < 64; ++i) {
		f.reset_prec(i);
		win.wait_for_button();
	}
}

template<typename T>
Fnct<T>::Fnct(std::function<double(double, T)> f, T prec, double r1, double r2, Point orig, int count, double xscale, double yscale)
	: f{f}, prec{prec}, r1{r1}, r2{r2}, orig{orig}, count{count}, xscale{xscale}, yscale{yscale}
{
	if (r2 - r1 <= 0)
		error("bad graphing range");
	if (count <= 0)
		error("non-positive graphing count");
	calculate_points();
}

template<typename T>
void Fnct<T>::draw_specifics(Painter& painter) const
{
	if (color().visibility() && 1<v.size())
		for (int i = 1; i<v.size(); ++i)
			painter.draw_line(v[i-1], v[i]);
}

template<typename T>
void Fnct<T>::move(int dx, int dy)
{
	orig.x += dx;
	orig.y += dy;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_func(std::function<double(double)> new_f)
{
	f = new_f;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_prec(T new_prec)
{
	prec = new_prec;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_range(double new_r1, double new_r2)
{
	if (new_r2 - new_r1 <= 0)
		error("bad graphing range");
	r1 = new_r1;
	r2 = new_r2;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_orig(Point new_orig)
{
	orig = new_orig;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_count(int new_count)
{
	if (count <= 0)
		error("non-positive graphing count");
	count = new_count;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::reset_scale(double new_xscale, double new_yscale)
{
	xscale = new_xscale;
	yscale = new_yscale;
	calculate_points();
	redraw();
}

template<typename T>
void Fnct<T>::calculate_points()
{
	v.clear();
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i < count; ++i) {
		v.push_back({orig.x+std::lround(r*xscale), orig.y-std::lround(f(r, prec)*yscale)});
		r += dist;
	}
}

double fac(int n)
{
	double r = 1;
	while (n>1) {
		r *= n;
		--n;
	}
	return r;
}

double term(double x, int n)
{
	return std::pow(x, n)/fac(n);
}

double exp_n(double x, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
		sum += term(x, i);
	return sum;
}
